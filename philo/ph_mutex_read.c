/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:01 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:15:19 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	read_state(t_philo *ph, t_state state)
{
	bool	ret;

	mutex_lock(&ph->mutex_state);
	ret = false;
	if (ph->state == state)
		ret = true;
	mutex_unlock(&ph->mutex_state);
	return (ret);
}

int	read_meals_eaten(t_philo *ph)
{
	int	ret;

	mutex_lock(&ph->mutex_meals_eaten);
	ret = ph->meals_eaten;
	mutex_unlock(&ph->mutex_meals_eaten);
	return (ret);
}

u_int64_t	read_last_meal(t_philo *ph)
{
	u_int64_t	ret;

	mutex_lock(&ph->mutex_last_meal);
	ret = ph->last_meal;
	mutex_unlock(&ph->mutex_last_meal);
	return (ret);
}

bool	read_done(t_philo *ph)
{
	bool	ret;

	mutex_lock(&ph->mutex_done);
	ret = ph->done;
	mutex_unlock(&ph->mutex_done);
	return (ret);
}
