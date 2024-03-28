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
	if (get_time() - read_last_meal(data) > data->time_to_die)
	{
		write_state(data, DEAD);
		display_msg(data, "died");
		exit_child(DEAD, data);
	}
	if (read_meals_eaten(data) == data->nbr_of_meals)
	{
		write_i_am_done(data, true);
		return (1);
		//sem_close(data->sem_full.sem);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!read_state(data, DEAD))
	{
		if (loop_monitor(data))
			break ;
		// usleep(1000);
	}
	return (NULL);
}

static void	routine_proc(t_data *data, int i)
{
	init_philos(data, i);
	if (pthread_create(&data->ph.thread_mon, NULL, &monitor, data))
		exit_error(E_THREAD, data);
	while (!read_i_am_done(data))
	{
		// if (data->nbr_of_meals != -1)
		// 	sem_wait(data->sem_full.sem);
		if (eat_routine(data))
			break ;
		usleep(100);
		if (sleep_routine(data))
			break ;
		usleep(100);
		if (think_routine(data))
			break ;
	}
	if (pthread_join(data->ph.thread_mon, NULL))
		exit_error(E_JOIN, data);
	exit_child(EATING, data);
}

static void	call_waitpid(t_data *data, int *status)
{
	int		i;

	i = -1;
	while (++i < data->ph_count)
	{
		waitpid(-1, status, 0);
		if (WEXITSTATUS(*status) == DEAD)
		{
			i = -1;
			while (++i < data->ph_count)
				kill(data->pid[i], SIGTERM);
			break ;
		}
		else if (WEXITSTATUS(*status) < 255 && WEXITSTATUS(*status) != 0)
			exit_error(WEXITSTATUS(*status), data);
	}
}

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
	call_waitpid(data, &status);
}
