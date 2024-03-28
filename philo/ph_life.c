/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 08:56:34 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_routine(t_philo *ph)
{
	if (read_state(ph, DEAD))
		return (1);
	write_state(ph, SLEEPING);
	if (read_state(ph, DEAD))
		return (1);
	display_msg(ph, "is sleeping");
	ft_usleep(ph->data->time_to_sleep);
	return (0);
}

int	think_routine(t_philo *ph)
{
	if (read_state(ph, DEAD))
		return (1);
	write_state(ph, THINKING);
	if (read_state(ph, DEAD))
		return (1);
	display_msg(ph, "is thinking");
	return (0);
}
