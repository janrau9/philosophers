/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 12:16:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sleep_routine(t_data *data)
{
	if (read_state(data, DEAD))
		return (1);
	write_state(data, SLEEPING);
	display_msg(data, "is sleeping");
	ft_usleep(data->time_to_sleep);
	return (0);
}

int	think_routine(t_data *data)
{
	if (read_state(data, DEAD))
		return (1);
	write_state(data, THINKING);
	display_msg(data, "is thinking");
	return (0);
}
