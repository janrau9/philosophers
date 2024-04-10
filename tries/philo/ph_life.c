/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 08:56:34 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_right_fork(t_philo *ph)
{
	if (read_died(ph))
		return (1);
	pthread_mutex_lock(ph->rght_frk);
	display_msg(ph, "has taken a fork");
	return (0);
}

static int	pick_left_fork(t_philo *ph)
{
	if (read_died(ph))
		return (1);
	if (ph->lft_frk == ph->rght_frk)
		return (1);
	pthread_mutex_lock(ph->lft_frk);
	display_msg(ph, "has taken a fork");
	return (0);
}

int	eat_routine(t_philo *ph)
{
	if (read_died(ph))
		return (1);
	if (pick_right_fork(ph))
		return (1);
	if (pick_left_fork(ph))
	{
		pthread_mutex_unlock(ph->rght_frk);
		return (1);
	}
	if (read_died(ph))
	{
		pthread_mutex_unlock(ph->lft_frk);
		pthread_mutex_unlock(ph->rght_frk);
		return (1);
	}
	write_last_meal(ph);
	display_msg(ph, "is eating");
	write_meals_eaten(ph);
	ft_usleep(ph->data->time_to_eat);
	pthread_mutex_unlock(ph->lft_frk);
	pthread_mutex_unlock(ph->rght_frk);
	return (0);
}

int	sleep_routine(t_philo *ph)
{
	if (read_died(ph))
		return (1);
	display_msg(ph, "is sleeping");
	ft_usleep(ph->data->time_to_sleep);
	return (0);
}

int	think_routine(t_philo *ph)
{
	if (read_died(ph))
		return (1);
	display_msg(ph, "is thinking");
	return (0);
}
