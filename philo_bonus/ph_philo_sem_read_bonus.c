/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_sem_read_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:31:01 by jberay            #+#    #+#             */
/*   Updated: 2024/03/01 11:31:03 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_state(t_data *data, t_state state)
{
	bool	ret;

	ret = false;
	sem_wait(data->ph.sem.sem);
	if (data->ph.state == state)
		ret = true;
	sem_post(data->ph.sem.sem);
	return (ret);
}

int	get_meals_eaten(t_data *data)
{
	int	ret;

	sem_wait(data->ph.sem.sem);
	ret = data->ph.meals_eaten;
	sem_post(data->ph.sem.sem);
	return (ret);
}

u_int64_t	get_last_meal(t_data *data)
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
