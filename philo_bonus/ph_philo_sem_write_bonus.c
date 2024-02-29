/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_write_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:07 by jberay            #+#    #+#             */
/*   Updated: 2024/02/28 13:28:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_i_am_done(t_philo *ph, bool value)
{
	sem_wait(ph->sem.sem);
	ph->i_am_done = value;
	sem_post(ph->sem.sem);
}

void	set_state(t_philo *ph, t_state state)
{
	sem_wait(ph->sem.sem);
	ph->state = state;
	sem_post(ph->sem.sem);
}

void	set_last_meal(t_philo *ph)
{
	sem_wait(ph->sem.sem);
	ph->last_meal = get_time();
	sem_post(ph->sem.sem);
}

void	set_meals_eaten(t_philo *ph)
{
	sem_wait(ph->sem.sem);
	ph->meals_eaten++;
	sem_post(ph->sem.sem);
}

void	display_msg(t_philo *ph, char *msg)
{
	u_int64_t	time;

	time = get_time() - ph->data->start_time;
	sem_wait(ph->data->sem_print.sem);
	printf("%llu %d %s\n", time, ph->id, msg);
	sem_post(ph->data->sem_print.sem);
}
