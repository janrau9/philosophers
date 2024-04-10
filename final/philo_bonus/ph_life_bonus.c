/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 12:16:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sleep_routine(t_data *data)
{
	display_msg(data, "is sleeping");
	ft_usleep(data->time_to_sleep);
	return (0);
}

int	think_routine(t_data *data)
{
	display_msg(data, "is thinking");
	return (0);
}

static int	pick_right_fork(t_data *data)
{
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

static int	pick_left_fork(t_data *data)
{
	if (read_died(data))
		return (1);
	if (data->ph_count == 1)
		return (1);
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

int	eat_routine(t_data *data)
{
	if (pick_right_fork(data))
		return (1);
	if (pick_left_fork(data))
	{
		sem_post(data->sem_forks.sem);
		return (1);
	}
	if (read_died(data))
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
