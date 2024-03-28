/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:12:59 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:36:24 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_right_fork(t_philo *ph)
{
	int	ret;

	if (read_state(ph, DEAD))
		return (1);
	ret = pthread_mutex_lock(ph->rght_frk);
	display_msg(ph, "has taken a fork");
	return (ret);
}

static int	pick_left_fork(t_philo *ph)
{
	int	ret;

	if (read_state(ph, DEAD))
		return (1);
	if (ph->lft_frk == ph->rght_frk)
		return (1);
	ret = pthread_mutex_lock(ph->lft_frk);
	display_msg(ph, "has taken a fork");
	return (ret);
}

static int	pickup_forks(t_philo *ph)
{
	if (pick_right_fork(ph))
		return (1);
	if (pick_left_fork(ph))
	{
		pthread_mutex_unlock(ph->rght_frk);
		return (1);
	}
	return (0);
}

int	eat_routine(t_philo *ph)
{
	if (read_state(ph, DEAD))
		return (1);
	if (pickup_forks(ph))
		return (1);
	if (read_state(ph, DEAD))
	{
		pthread_mutex_unlock(ph->lft_frk);
		pthread_mutex_unlock(ph->rght_frk);
		return (1);
	}
	write_last_meal(ph);
	write_state(ph, EATING);
	display_msg(ph, "is eating");
	ft_usleep(ph->data->time_to_eat);
	write_meals_eaten(ph);
	pthread_mutex_unlock(ph->lft_frk);
	pthread_mutex_unlock(ph->rght_frk);
	return (0);
}
