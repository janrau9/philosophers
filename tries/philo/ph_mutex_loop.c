/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:07:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:00:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	while (mutex->locked)
	{
		pthread_mutex_unlock(&mutex->mutex);
		usleep(100);
		pthread_mutex_lock(&mutex->mutex);
	}
	mutex->locked = 1;
	pthread_mutex_unlock(&mutex->mutex);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->locked = 0;
	pthread_mutex_unlock(&mutex->mutex);
}
