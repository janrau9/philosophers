/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:13:51 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:13:37 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
		return (E_MUTEX);
	mutex->locked = false;
	mutex->init = true;
	return (0);
}

int	to_malloc(t_data *data)
{
	data->thd_ph = malloc(sizeof(pthread_t) * data->ph_count);
	if (!data->thd_ph)
		return (E_MALLOC);
	data->forks = malloc(sizeof(t_mutex) * data->ph_count);
	if (!data->forks)
		return (E_MALLOC);
	data->phs = malloc(sizeof(t_philo) * data->ph_count);
	if (!data->phs)
		return (E_MALLOC);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (init_mutex(&data->mutex_msg))
		return (E_MUTEX);
	i = -1;
	while (++i < data->ph_count)
	{
		if (init_mutex(&data->forks[i]))
			return (E_MUTEX);
	}
	return (0);
}

static void	set_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_count)
	{
		data->phs[i].rght_frk = &data->forks[i].mutex;
		data->phs[i].lft_frk = &data->forks[(i + 1) % data->ph_count].mutex;
	}
}

int	init_philos(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->ph_count)
	{
		data->phs[i].id = i + 1;
		data->phs[i].meals_eaten = 0;
		data->phs[i].data = data;
		data->phs[i].done = false;
		data->phs[i].state = THINKING;
		data->phs[i].last_meal = data->start_time;
		if (init_mutex(&data->phs[i].mutex_last_meal))
			return (E_MUTEX);
		if (init_mutex(&data->phs[i].mutex_meals_eaten))
			return (E_MUTEX);
		if (init_mutex(&data->phs[i].mutex_state))
			return (E_MUTEX);
		if (init_mutex(&data->phs[i].mutex_done))
			return (E_MUTEX);
	}
	set_forks(data);
	return (0);
}
