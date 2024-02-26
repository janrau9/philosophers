/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_data_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:07:33 by jberay            #+#    #+#             */
/*   Updated: 2024/02/23 09:16:43 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static u_int64_t	get_time_to_die(t_philo *ph)
{
	u_int64_t	ret;

	pthread_mutex_lock(&ph->data->mutex[TIME_TO_DIE].mutex);
	ret = ph->data->time_to_die;
	pthread_mutex_unlock(&ph->data->mutex[TIME_TO_DIE].mutex);
	return (ret);
}

static u_int64_t	get_time_to_eat(t_philo *ph)
{
	u_int64_t	ret;

	pthread_mutex_lock(&ph->data->mutex[TIME_TO_EAT].mutex);
	ret = ph->data->time_to_eat;
	pthread_mutex_unlock(&ph->data->mutex[TIME_TO_EAT].mutex);
	return (ret);
}

static u_int64_t	get_time_to_sleep(t_philo *ph)
{
	u_int64_t	ret;

	pthread_mutex_lock(&ph->data->mutex[TIME_TO_SLEEP].mutex);
	ret = ph->data->time_to_sleep;
	pthread_mutex_unlock(&ph->data->mutex[TIME_TO_SLEEP].mutex);
	return (ret);
}

static u_int64_t	get_start_time(t_philo *ph)
{
	u_int64_t	ret;

	pthread_mutex_lock(&ph->data->mutex[TIME_START].mutex);
	ret = ph->data->start_time;
	pthread_mutex_unlock(&ph->data->mutex[TIME_START].mutex);
	return (ret);
}

u_int64_t	get_mutex_time(t_philo *ph, t_data_locks lock)
{
	if (lock == TIME_START)
		return (get_start_time(ph));
	else if (lock == TIME_TO_DIE)
		return (get_time_to_die(ph));
	else if (lock == TIME_TO_EAT)
		return (get_time_to_eat(ph));
	else if (lock == TIME_TO_SLEEP)
		return (get_time_to_sleep(ph));
	return (0);
}
