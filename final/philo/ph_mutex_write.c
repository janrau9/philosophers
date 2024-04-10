/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:07 by jberay            #+#    #+#             */
/*   Updated: 2024/04/02 15:07:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_died(t_philo *ph)
{
	mutex_lock(&ph->data->mutex_died);
	ph->data->died = true;
	mutex_unlock(&ph->data->mutex_died);
}

void	write_last_meal(t_philo *ph)
{
	mutex_lock(&ph->mutex_last_meal);
	ph->last_meal = get_time();
	mutex_unlock(&ph->mutex_last_meal);
}

void	write_meals_eaten(t_philo *ph)
{
	mutex_lock(&ph->mutex_meals_eaten);
	ph->meals_eaten++;
	mutex_unlock(&ph->mutex_meals_eaten);
}

void	write_done(t_philo *ph)
{
	mutex_lock(&ph->mutex_done);
	ph->done = true;
	mutex_unlock(&ph->mutex_done);
}

void	display_msg(t_philo *ph, char *msg)
{
	u_int64_t	time;

	mutex_lock(&ph->data->mutex_msg);
	time = get_time() - ph->data->start_time;
	if (!read_died(ph))
		printf("%llu %d %s\n", time, ph->id, msg);
	mutex_unlock(&ph->data->mutex_msg);
}
