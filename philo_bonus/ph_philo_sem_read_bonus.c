/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_read_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:01 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:55:15 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_state(t_philo *ph, t_state state)
{
	bool	ret;

	ret = false;
	sem_close(ph->data->sem_dead.sem);
	sem_wait(ph->sem.sem);
	if (ph->state == state)
		ret = true;
	sem_post(ph->sem.sem);
	return (ret);
}

int	get_meals_eaten(t_philo *ph)
{
	int	ret;

	sem_wait(ph->sem.sem);
	ret = ph->meals_eaten;
	sem_post(ph->sem.sem);
	return (ret);
}

bool	read_i_am_done(t_philo *ph)
{
	bool	ret;

	sem_wait(ph->sem.sem);
	ret = ph->i_am_done;
	sem_post(ph->sem.sem);
	return (ret);
}

u_int64_t	get_last_meal(t_philo *ph)
{
	u_int64_t	ret;

	sem_wait(ph->sem.sem);
	ret = ph->last_meal;
	sem_post(ph->sem.sem);
	return (ret);
}

bool	dead_philos(t_data *data)
{
	bool	ret;

	ret = true;
	data->sem_dead.sem = sem_open(SEM_DEAD, AT_EACCESS, 0644, 0);
	if (data->sem_dead.sem == SEM_FAILED)
		ret = false;
	else
		set_state(&data->ph, DEAD);
	sem_close(data->sem_dead.sem);
	return (ret);
}