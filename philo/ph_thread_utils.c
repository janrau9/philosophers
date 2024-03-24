/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:26 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 11:08:01 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_msg(t_philo *ph, char *msg)
{
	u_int64_t	time;

	time = get_time() - get_mutex_time(ph, TIME_START);
	pthread_mutex_lock(&ph->data->mutex[MSG].mutex);
	if (check_state(ph, DEAD) && !get_mutex_flag(ph, SOMEONE_DIED))
	{
		printf("%lu %d %s\n", time, ph->id, msg);
		set_someone_died(ph, true);
	}
	else if (!check_state(ph, DEAD) && !get_mutex_flag(ph, SOMEONE_DIED))
		printf("%lu %d %s\n", time, ph->id, msg);
	pthread_mutex_unlock(&ph->data->mutex[MSG].mutex);
}

void	set_someone_died(t_philo *ph, bool value)
{
	pthread_mutex_lock(&ph->data->mutex[SOMEONE_DIED].mutex);
	ph->data->someone_died = value;
	pthread_mutex_unlock(&ph->data->mutex[SOMEONE_DIED].mutex);
}

void	set_done(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->mutex[DONE].mutex);
	ph->data->all_done++;
	pthread_mutex_unlock(&ph->data->mutex[DONE].mutex);
}
