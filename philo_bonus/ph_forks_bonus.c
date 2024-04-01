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
		write_died(data);
		sem_wait(data->sem_print.sem);
		time = get_time() - data->start_time;
		printf("%lu %d %s\n", time, data->ph.id, "died");
		sem_post(data->sem_print.sem);
		sem_post(data->sem_full.sem);
		write_someone_died(data);
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
	while (1)
	{
		if (read_someone_died(data))
		{
			write_died(data);
			sem_post(data->sem_full.sem);
			break;
		}
		if (loop_monitor(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

static void	routine_proc(t_data *data, int i)
{
	if (data->nbr_of_meals != -1)
		sem_wait(data->sem_full.sem);
	init_philos(data, i);
	if (pthread_create(&data->ph.thread_mon, NULL, &monitor, data))
		exit_error(E_THREAD, data);
	while (1)
	{

		if (eat_routine(data) || read_died(data))
			break ;
		if (sleep_routine(data) || read_died(data))
			break ;
		if (think_routine(data) || read_died(data))
			break ;
	}
	if (pthread_join(data->ph.thread_mon, NULL))
		exit_error(E_JOIN, data);
	exit_child(E_DIED, data);
}

/* void	call_wait(t_data *data)
{
	int	i;

	if (data->nbr_of_meals != -1)
	{
		i = -1;
		usleep(60000);
		while (++i < data->ph_count)
			sem_wait(data->sem_full.sem);
		write_full();
	}
	i = -1;
	while (++i < data->ph_count)
		waitpid(-1, NULL, 0);
} */

void	start_fork(t_data *data)
{
	int	i;

	data->pid = malloc(sizeof(int) * data->ph_count);
	if (data->pid == NULL)
		exit_error(E_MALLOC, data);
	i = -1;
	while (++i < data->ph_count)
	{
		if (i == data->ph_count - 1)
			usleep(10000);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit_error(E_FORK, data);
		if (data->pid[i] == 0)
			routine_proc(data, i);
	}
	if (data->nbr_of_meals != -1)
	{
		i = -1;
		ft_usleep(60);
		while (++i < data->ph_count)
			sem_wait(data->sem_full.sem);
		write_full(data);
	}
	i = -1;
	while (++i < data->ph_count)
		waitpid(-1, NULL, 0);
	//call_wait(data);
}
