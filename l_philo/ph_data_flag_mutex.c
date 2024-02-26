/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_data_flag_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:22:56 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 08:55:32 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_nbr_of_meals(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->data->mutex[NBR_OF_MEALS].mutex);
	ret = ph->data->nbr_of_meals;
	pthread_mutex_unlock(&ph->data->mutex[NBR_OF_MEALS].mutex);
	return (ret);
}

static int	get_ph_count(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->data->mutex[PH_COUNT].mutex);
	ret = ph->data->ph_count;
	pthread_mutex_unlock(&ph->data->mutex[PH_COUNT].mutex);
	return (ret);
}

static int	get_done(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->data->mutex[DONE].mutex);
	ret = ph->data->all_done;
	pthread_mutex_unlock(&ph->data->mutex[DONE].mutex);
	return (ret);
}

static int	get_someone_died(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->data->mutex[SOMEONE_DIED].mutex);
	ret = ph->data->someone_died;
	pthread_mutex_unlock(&ph->data->mutex[SOMEONE_DIED].mutex);
	return (ret);
}

int	get_mutex_flag(t_philo *ph, t_data_locks lock)
{
	if (lock == NBR_OF_MEALS)
		return (get_nbr_of_meals(ph));
	else if (lock == PH_COUNT)
		return (get_ph_count(ph));
	else if (lock == DONE)
		return (get_done(ph));
	else if (lock == SOMEONE_DIED)
		return (get_someone_died(ph));
	return (0);
}