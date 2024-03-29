/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:30:25 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 15:21:13 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	loop_monitor(t_data *data)
{
	u_int64_t	time;

	if (get_time() - read_last_meal(data) > data->time_to_die)
	{
		write_died();
		sem_wait(data->sem_print.sem);
		time = get_time() - data->start_time;
		printf("%lu %d %s\n", time, data->ph.id, "died");
		sem_post(data->sem_print.sem);
		return (1);
	}
	if (read_meals_eaten(data) == data->nbr_of_meals && !read_i_am_done(data))
	{
		//printf("Philosopher %d is done eating\n", data->ph.id);
		write_i_am_done(data, true);
		sem_post(data->sem_full.sem);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!read_died())
	{
		if (loop_monitor(data))
			break ;
	}
	return (NULL);
}

static void	routine_proc(t_data *data, int i)
{
	init_philos(data, i);
	if (pthread_create(&data->ph.thread_mon, NULL, &monitor, data))
		exit_error(E_THREAD, data);
	if (data->nbr_of_meals != -1)
		sem_wait(data->sem_full.sem);
	while (!read_died())
	{
		if (eat_routine(data))
			break ;
		if (sleep_routine(data))
			break ;
		if (think_routine(data))
			break ;
	}
	if (pthread_join(data->ph.thread_mon, NULL))
		exit_error(E_JOIN, data);
	sem_post(data->sem_full.sem);
	exit_child(E_DIED, data);
}

/* static void	call_waitpid(t_data *data, int *status)
{
	int		i;

	i = -1;
	while (++i < data->ph_count)
	{
		waitpid(-1, status, 0);
		if (WEXITSTATUS(*status) == E_DIED)
		{
			i = -1;
			while (++i < data->ph_count)
				kill(data->pid[i], SIGTERM);
			break ;
		}
		else if (WEXITSTATUS(*status) < 255 && WEXITSTATUS(*status) != 0)
			exit_error(WEXITSTATUS(*status), data);
	}
} */

void	start_fork(t_data *data)
{
	int	i;
	int	status;

	data->pid = malloc(sizeof(int) * data->ph_count);
	if (data->pid == NULL)
		exit_error(E_MALLOC, data);
	i = -1;
	while (++i < data->ph_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit_error(E_FORK, data);
		if (data->pid[i] == 0)
			routine_proc(data, i);
	}
	if (data->nbr_of_meals != -1)
	{
		i = -1;
		usleep(10000);
		while (++i < data->ph_count)
			sem_wait(data->sem_full.sem);
		//printf("All philosophers are done eating\n");
		write_died();
	}
	i = -1;
	while (++i < data->ph_count)
		waitpid(-1, &status, 0);
	
	//call_waitpid(data, &status);
}
