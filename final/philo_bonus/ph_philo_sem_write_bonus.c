/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_write_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:07 by jberay            #+#    #+#             */
/*   Updated: 2024/04/03 08:14:28 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_someone_died(t_data *data)
{
	sem_wait(data->ph.sem.sem);
	data->sem_died.sem = sem_open(SEM_DIED, O_CREAT, 0644, 1);
	sem_post(data->ph.sem.sem);
}

void	write_died(t_data *data)
{
	sem_wait(data->ph.sem.sem);
	data->ph.died = true;
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

void	write_i_am_done(t_data *data, bool value)
{
	sem_wait(data->ph.sem.sem);
	data->ph.i_am_done = value;
	sem_post(data->ph.sem.sem);
}
