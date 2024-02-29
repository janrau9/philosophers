/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:59:09 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:53:57 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define SEM_NAME "/philosopher"
# define SEM_FORK "/forks"
# define SEM_PRINT "/print"
# define SEM_DEAD "/dead"

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

typedef struct s_sem
{
	sem_t	*sem;
	bool	init;
}			t_sem;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			i_am_done;
	t_state			state;
	u_int64_t		last_meal;
	t_sem			sem;
	pthread_t		thread_mon;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	int				nbr_of_meals;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	t_sem			sem_forks;
	t_sem			sem_print;
	t_sem			sem_dead;
	t_philo			ph;
	int				*pid;
}					t_data;

/*check args*/
int			check_input(char **argv);
int			check_args(t_data *data, char **argv);

/*initialize data*/
int			to_malloc(t_data *data);
void		set_forks(t_data *data);
void		init_philos(t_data *data, int i);

/*life*/
int			eat_routine(t_philo *ph);
int			sleep_routine(t_philo *ph);
int			think_routine(t_philo *ph);

/*threads*/
int			start_fork(t_data *data);

/*monitor mutex*/
void		display_msg(t_philo *ph, char *msg);

/*philo mutex read*/
bool		read_i_am_done(t_philo *ph);
int			get_meals_eaten(t_philo *ph);
bool		check_state(t_philo *ph, t_state state);
u_int64_t	get_last_meal(t_philo *ph);
bool		dead_philos(t_data *data);

/*philo mutex write*/
void		write_i_am_done(t_philo *ph, bool value);
void		set_state(t_philo *ph, t_state state);
void		set_meals_eaten(t_philo *ph);
void		set_last_meal(t_philo *ph);

/*utils*/
void		ft_usleep(u_int64_t time);
u_int64_t	get_time(void);
long		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);

/*error*/
int			ret_error(t_error error, t_data *data);

#endif