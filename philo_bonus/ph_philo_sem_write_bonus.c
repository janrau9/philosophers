/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_write_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 14:29:59 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_state(t_data *data, t_state state)
{
	sem_wait(data->ph.sem.sem);
	data->ph.state = state;
	sem_post(data->ph.sem.sem);
}

void	write_last_meal(t_data *data)
{
	sem_wait(data->ph.sem.sem);
	data->ph.last_meal = get_time();
	sem_post(data->ph.sem.sem);
}

void	write_meals_eaten(t_data *data)
{
	sem_wait(data->ph.sem.sem);
	data->ph.meals_eaten++;
	sem_post(data->ph.sem.sem);
}

void	display_msg(t_data *data, char *msg)
{
	u_int64_t	time;

	sem_wait(data->sem_print.sem);
	time = get_time() - data->start_time;
	printf("%llu %d %s\n", time, data->ph.id, msg);
	sem_post(data->sem_print.sem);
}

void	write_i_am_done(t_data *data, bool value)
{
	sem_wait(data->ph.sem.sem);
	data->ph.i_am_done = value;
	sem_post(data->ph.sem.sem);
}
