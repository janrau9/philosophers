/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:12:59 by jberay            #+#    #+#             */
/*   Updated: 2024/03/01 09:51:22 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	pick_right_fork(t_data *data)
{
	if (read_i_am_done(data))
		return (1);
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

static int	pick_left_fork(t_data *data)
{
	if (read_i_am_done(data))
		return (1);
	if (data->ph_count == 1)
		return (1);
	sem_wait(data->sem_forks.sem);
	display_msg(data, "has taken a fork");
	return (0);
}

static int	pickup_forks(t_data *data)
{
	if (read_i_am_done(data))
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
	if (read_i_am_done(data))
	{
		sem_post(data->sem_forks.sem);
		sem_post(data->sem_forks.sem);
		return (1);
	}
	set_last_meal(data);
	set_state(data, EATING);
	display_msg(data, "is eating");
	ft_usleep(data->time_to_eat);
	set_meals_eaten(data);
	sem_post(data->sem_forks.sem);
	sem_post(data->sem_forks.sem);
	return (0);
}
