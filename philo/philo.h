/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:59:09 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:31:38 by jberay           ###   ########.fr       */
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
	DONE
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

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				locked;
	bool			init;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			done;
	t_state			state;
	u_int64_t		last_meal;
	pthread_mutex_t	*lft_frk;
	pthread_mutex_t	*rght_frk;
	t_mutex			mutex_last_meal;
	t_mutex			mutex_meals_eaten;
	t_mutex			mutex_state;
	t_mutex			mutex_done;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	bool			someone_died;
	int				nbr_of_meals;
	int				nbr_done;
	pthread_t		*thd_ph;
	pthread_t		thd_mon;
	t_mutex			*forks;
	t_mutex			mutex_msg;
	t_mutex			mutex_mon;
	t_philo			*phs;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
}					t_data;

/*check args*/
int			check_input(char **argv);
int			check_args(t_data *data, char **argv);

/*initialize data*/
int			to_malloc(t_data *data);
int			init_mutexes(t_data *data);
int			init_philos(t_data *data);

/*life*/
int			eat_routine(t_philo *ph);
int			sleep_routine(t_philo *ph);
int			think_routine(t_philo *ph);

/*threads*/
int			start_threads(t_data *data);

/*mutex loop*/
void		mutex_lock(t_mutex *mutex);
void		mutex_unlock(t_mutex *mutex);

/*mutex reads*/
bool		read_state(t_philo *ph, t_state state);
int			read_meals_eaten(t_philo *ph);
u_int64_t	read_last_meal(t_philo *ph);
bool		read_done(t_philo *ph);

/*mutex writes*/
void		write_state(t_philo *ph, t_state state);
void		write_last_meal(t_philo *ph);
void		write_meals_eaten(t_philo *ph);
void		write_done(t_philo *ph);

/*monitor mutex*/
void		display_msg(t_philo *ph, char *msg);

/*utils*/
void		ft_usleep(u_int64_t time);
u_int64_t	get_time(void);

/*error*/
int			ret_error(t_error error, t_data *data);

#endif