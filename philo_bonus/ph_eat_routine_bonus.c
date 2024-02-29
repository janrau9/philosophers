/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:12:59 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:56:01 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	pick_right_fork(t_philo *ph)
{
	if (check_state(ph, DEAD) || read_i_am_done(ph))
		return (1);
	sem_wait(ph->data->sem_forks.sem);
	display_msg(ph, "has taken a fork");
	return (0);
}

static int	pick_left_fork(t_philo *ph)
{
	if (check_state(ph, DEAD) || read_i_am_done(ph))
		return (1);
	if (ph->data->ph_count == 1)
		return (1);
	sem_wait(ph->data->sem_forks.sem);
	display_msg(ph, "has taken a fork");
	return (0);
}

static int	pickup_forks(t_philo *ph)
{
	if (check_state(ph, DEAD) || read_i_am_done(ph))
		return (1);
	if (pick_right_fork(ph))
		return (1);
	if (pick_left_fork(ph))
	{
		sem_post(ph->data->sem_forks.sem);
		return (1);
	}
	return (0);
}

int	eat_routine(t_philo *ph)
{
	if (pickup_forks(ph))
		return (1);
	if (check_state(ph, DEAD) || read_i_am_done(ph))
	{
		sem_post(ph->data->sem_forks.sem);
		sem_post(ph->data->sem_forks.sem);
		return (1);
	}
	set_last_meal(ph);
	set_state(ph, EATING);
	display_msg(ph, "is eating");
	ft_usleep(ph->data->time_to_eat);
	set_meals_eaten(ph);
	sem_post(ph->data->sem_forks.sem);
	sem_post(ph->data->sem_forks.sem);
	return (0);
}
