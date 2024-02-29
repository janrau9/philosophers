/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:30 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:53:50 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	loop_monitor(t_philo *ph)
{
	if (get_time() - get_last_meal(ph) > ph->data->time_to_die)
	{
		set_state(ph, DEAD);
		display_msg(ph, "died");
		ph->data->sem_dead.sem = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
		if (ph->data->sem_dead.sem == SEM_FAILED)
			return (1);
	}
	if (get_meals_eaten(ph) == ph->data->nbr_of_meals
		&& read_i_am_done(ph) == false)
	{
		write_i_am_done(ph, true);
		return (1);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!check_state(ph, DEAD) && !read_i_am_done(ph))
	{
		if (loop_monitor(ph))
			break ;
	}
	return (NULL);
}

static int	routine_proc(t_data *data, int i)
{
	init_philos(data, i);
	if (data->ph.id % 2 == 0)
		ft_usleep(data->time_to_eat / 2);
	if (pthread_create(&data->ph.thread_mon, NULL, &monitor, &data->ph))
		return (ret_error(E_THREAD, data));
	while (!check_state(&data->ph, DEAD) && !read_i_am_done(&data->ph) && !dead_philos(data))
	{
		if (eat_routine(&data->ph))
			break ;
		if (sleep_routine(&data->ph))
			break ;
		if (think_routine(&data->ph))
			break ;
	}
	if (pthread_join(data->ph.thread_mon, NULL))
		return (ret_error(E_JOIN, data));
	if (check_state(&data->ph, DEAD))
		exit(DEAD);
	exit(NO_ERROR);
}

int	start_fork(t_data *data)
{
	int		i;
	// pid_t	pid;
	int		status;

	data->pid = malloc(sizeof(int) * data->ph_count);

	i = -1;
	while (++i < data->ph_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (ret_error(E_THREAD, data));
		if (data->pid[i] == 0)
		{
			routine_proc(data, i);
			return (0);
		}
	}
	i = -1;
	while (++i < data->ph_count)
		waitpid(data->pid[i], &status, 0);
	// while (1)
	// {
	// 	waitpid(0, &status, WNOHANG);
	// 	if (WEXITSTATUS(status) == DEAD)
	// 	{
	// 		while (--i > -1)
	// 			kill(data->pid[i], SIGTERM);
	// 		return (DEAD);
	// 	}
	// }
	return (0);
}
