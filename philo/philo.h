/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:59:09 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 11:12:13 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}			t_state;

typedef enum e_error
{
	NO_ERROR,
	E_ARGS,
	E_MALLOC,
	E_THREAD,
	E_JOIN,
	E_MUTEX
}			t_error;

typedef enum e_data_locks
{
	MSG,
	DONE,
	NBR_OF_MEALS,
	PH_COUNT,
	SOMEONE_DIED,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TIME_START
}			t_data_locks;

typedef enum e_philo_locks
{
	STATE,
	MEALS_EATEN,
	LAST_MEAL,
	I_AM_DONE
}			t_philo_locks;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			init;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			i_am_done;
	t_state			state;
	u_int64_t		last_meal;
	pthread_mutex_t	*lft_frk;
	pthread_mutex_t	*rght_frk;
	t_mutex			mutex[4];
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	bool			someone_died;
	int				nbr_of_meals;
	int				all_done;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	pthread_t		*thread_ph;
	pthread_t		thread_mon;
	t_mutex			*forks;
	t_mutex			mutex[8];
	t_philo			*phs;
}					t_data;

/*check args*/
int			check_input(char **argv);
int			check_args(t_data *data, char **argv);

/*initialize data*/
void		init_data(t_data *data);
int			to_malloc(t_data *data);
void		set_forks(t_data *data);
void		init_philos(t_data *data);

/*life*/
int			eat_routine(t_philo *ph);
int			sleep_routine(t_philo *ph);
int			think_routine(t_philo *ph);

/*threads*/
int			start_threads(t_data *data);

/*monitor mutex*/
void		set_someone_died(t_philo *ph, bool value);
void		display_msg(t_philo *ph, char *msg);
void		set_done(t_philo *ph);

/*data mutexes*/
int			get_mutex_flag(t_philo *ph, t_data_locks lock);
u_int64_t	get_mutex_time(t_philo *ph, t_data_locks lock);

/*philo mutex read*/
bool		read_i_am_done(t_philo *ph);
int			get_meals_eaten(t_philo *ph);
bool		check_state(t_philo *ph, t_state state);
u_int64_t	get_last_meal(t_philo *ph);

/*philo mutex write*/
void		write_i_am_done(t_philo *ph, bool value);
void		set_state(t_philo *ph, t_state state);
void		set_meals_eaten(t_philo *ph);
void		set_last_meal(t_philo *ph);

/*utils*/
void		ft_usleep(u_int64_t time);
u_int64_t	get_time(void);
long		ft_atoi(const char *str);

/*error*/
int			ret_error(t_error error, t_data *data);

#endif