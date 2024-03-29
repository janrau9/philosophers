/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:12:59 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 15:15:58 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	pick_right_fork(t_data *data)
{
	if (read_died())
		return (1);
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

static int	pick_left_fork(t_data *data)
{
	if (read_died())
		return (1);
	if (data->ph_count == 1)
		return (1);
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

static int	pickup_forks(t_data *data)
{
	if (read_died())
		return (1);
	if (pick_right_fork(data))
		return (1);
	if (pick_left_fork(data))
	{
		sem_post(data->sem_forks.sem);
		return (1);
	}
	return (0);
}

int	eat_routine(t_data *data)
{
	if (pickup_forks(data))
		return (1);
	if (read_died())
	{
		sem_post(data->sem_forks.sem);
		sem_post(data->sem_forks.sem);
		return (1);
	}
	write_last_meal(data);
	display_msg(data, "is eating");
	write_meals_eaten(data);
	ft_usleep(data->time_to_eat);
	sem_post(data->sem_forks.sem);
	sem_post(data->sem_forks.sem);
	return (0);
}
