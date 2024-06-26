/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:59:09 by jberay            #+#    #+#             */
/*   Updated: 2024/04/03 08:39:44 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
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
# define SEM_FULL "/full"
# define SEM_DIED "/died"

typedef enum e_error
{
	NO_ERROR,
	E_ARGS,
	E_MALLOC,
	E_THREAD,
	E_JOIN,
	E_SEM,
	E_FORK,
	E_DIED
}			t_error;

typedef struct s_sem
{
	sem_t	*sem;
	bool	init;
	int		locked;
}			t_sem;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			i_am_done;
	bool			died;
	u_int64_t		last_meal;
	t_sem			sem;
	pthread_t		thread_mon;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	int				nbr_of_meals;
	int				*pid;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	t_sem			sem_forks;
	t_sem			sem_print;
	t_sem			sem_full;
	t_sem			sem_died;
	t_sem			sem_mon;
	t_philo			ph;
}					t_data;

/*check args*/
int			check_input(char **argv);
void		check_args(t_data *data, char **argv);

/*initialize data*/
void		init_data(t_data *data);
void		set_forks(t_data *data);
void		init_philos(t_data *data, int i);

/*life*/
int			eat_routine(t_data *data);
int			sleep_routine(t_data *data);
int			think_routine(t_data *data);

/*fork()*/
void		start_fork(t_data *data);

/*philo sem read*/
int			read_meals_eaten(t_data *data);
bool		read_died(t_data *data);
u_int64_t	read_last_meal(t_data *data);
bool		read_i_am_done(t_data *data);
bool		read_someone_died(t_data *data);

/*philo sem write*/
void		write_died(t_data *data);
void		write_meals_eaten(t_data *data);
void		write_last_meal(t_data *data);
void		write_i_am_done(t_data *data, bool value);
void		display_msg(t_data *data, char *msg);
void		write_full(t_data *data);
void		write_someone_died(t_data *data);

/*utils*/
void		ft_usleep(u_int64_t time);
u_int64_t	get_time(void);
long		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);

/*error*/
void		exit_error(t_error error, t_data *data);
void		exit_child(t_error error, t_data *data);

#endif