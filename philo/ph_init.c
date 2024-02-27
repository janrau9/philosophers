/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:13:51 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 08:59:52 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (++i < 8)
	{
		pthread_mutex_init(&data->mutex[i].mutex, NULL);
		data->mutex[i].init = true;
	}
	i = -1;
	while (++i < data->ph_count)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].init = true;
	}
}

void	init_data(t_data *data)
{
	data->start_time = get_time();
	data->someone_died = false;
	data->all_done = 0;
	data->thread_ph = NULL;
	data->thread_mon = NULL;
	data->forks = NULL;
	data->phs = NULL;
}

int	to_malloc(t_data *data)
{
	data->thread_ph = malloc(sizeof(pthread_t) * data->ph_count);
	if (!data->thread_ph)
		return (E_MALLOC);
	data->forks = malloc(sizeof(t_mutex) * data->ph_count);
	if (!data->forks)
		return (E_MALLOC);
	data->phs = malloc(sizeof(t_philo) * data->ph_count);
	if (!data->phs)
		return (E_MALLOC);
	return (0);
}

void	set_forks(t_data *data)
{
	int	i;

	i = -1;
	init_mutex(data);
	while (++i < data->ph_count)
	{
		data->phs[i].rght_frk = &data->forks[i].mutex;
		data->phs[i].lft_frk = &data->forks[(i + 1) % data->ph_count].mutex;
	}
}

void	init_philos(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->ph_count)
	{
		data->phs[i].data = data;
		data->phs[i].id = i + 1;
		data->phs[i].last_meal = data->start_time;
		data->phs[i].state = THINKING;
		data->phs[i].meals_eaten = 0;
		data->phs[i].i_am_done = false;
		while (++j < 4)
		{
			pthread_mutex_init(&data->phs[i].mutex[j].mutex, NULL);
			data->phs[i].mutex[j].init = true;
		}
	}
}
