/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:01 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 09:01:06 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	check_state(t_philo *ph, t_state state)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&ph->mutex[STATE].mutex);
	if (ph->state == state)
		ret = true;
	pthread_mutex_unlock(&ph->mutex[STATE].mutex);
	return (ret);
}

int	get_meals_eaten(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->mutex[MEALS_EATEN].mutex);
	ret = ph->meals_eaten;
	pthread_mutex_unlock(&ph->mutex[MEALS_EATEN].mutex);
	return (ret);
}

void	set_meals_eaten(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex[MEALS_EATEN].mutex);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->mutex[MEALS_EATEN].mutex);
}

bool	read_i_am_done(t_philo *ph)
{
	bool	ret;

	pthread_mutex_lock(&ph->mutex[I_AM_DONE].mutex);
	ret = ph->i_am_done;
	pthread_mutex_unlock(&ph->mutex[I_AM_DONE].mutex);
	return (ret);
}

void	write_i_am_done(t_philo *ph, bool value)
{
	pthread_mutex_lock(&ph->mutex[I_AM_DONE].mutex);
	ph->i_am_done = value;
	pthread_mutex_unlock(&ph->mutex[I_AM_DONE].mutex);
}

u_int64_t	get_last_meal(t_philo *ph)
{
	u_int64_t	ret;

	pthread_mutex_lock(&ph->mutex[LAST_MEAL].mutex);
	ret = ph->last_meal;
	pthread_mutex_unlock(&ph->mutex[LAST_MEAL].mutex);
	return (ret);
}
