/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_read_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:31:01 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 12:09:36 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	read_someone_died(t_data *data)
{
	sem_t	*sem;

	sem_wait(data->ph.sem.sem);
	unlink(SEM_DIED);
	sem = sem_open(SEM_DIED, O_RDONLY, 0644, 1);
	if (sem == SEM_FAILED)
	{
		sem_post(data->ph.sem.sem);
		return (false);
	}
	sem_close(sem);
	unlink(SEM_DIED);
	//printf("%d Philosopher killed\n", data->ph.id);
	sem_post(data->ph.sem.sem);
	return (true);
}
bool	read_died(t_data *data)
{
	bool	ret;

	sem_wait(data->ph.sem.sem);
	ret = false;
	if (data->ph.died)
		ret = true;
	sem_post(data->ph.sem.sem);
	return (ret);
}

int	read_meals_eaten(t_data *data)
{
	int	ret;

	sem_wait(data->ph.sem.sem);
	ret = data->ph.meals_eaten;
	sem_post(data->ph.sem.sem);
	return (ret);
}

u_int64_t	read_last_meal(t_data *data)
{
	u_int64_t	ret;

	sem_wait(data->ph.sem.sem);
	ret = data->ph.last_meal;
	sem_post(data->ph.sem.sem);
	return (ret);
}

bool	read_i_am_done(t_data *data)
{
	bool	ret;

	sem_wait(data->ph.sem.sem);
	ret = data->ph.i_am_done;
	sem_post(data->ph.sem.sem);
	return (ret);
}
