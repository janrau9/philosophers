/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_mutex_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:07 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 10:45:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_i_am_done(t_philo *ph, bool value)
{
	pthread_mutex_lock(&ph->mutex[I_AM_DONE].mutex);
	ph->i_am_done = value;
	pthread_mutex_unlock(&ph->mutex[I_AM_DONE].mutex);
}

void	set_state(t_philo *ph, t_state state)
{
	pthread_mutex_lock(&ph->mutex[STATE].mutex);
	ph->state = state;
	pthread_mutex_unlock(&ph->mutex[STATE].mutex);
}

void	set_last_meal(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex[LAST_MEAL].mutex);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->mutex[LAST_MEAL].mutex);
}

void	set_meals_eaten(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex[MEALS_EATEN].mutex);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->mutex[MEALS_EATEN].mutex);
}
