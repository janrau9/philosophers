/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 08:47:47 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_routine(t_philo *ph)
{
	if (check_state(ph, DEAD)
		&& read_i_am_done(ph))
		return (1);
	set_state(ph, SLEEPING);
	display_msg(ph, "is sleeping");
	ft_usleep(ph->data->time_to_sleep);
	return (0);
}

int	think_routine(t_philo *ph)
{
	if (check_state(ph, DEAD)
		&& read_i_am_done(ph))
		return (1);
	set_state(ph, THINKING);
	display_msg(ph, "is thinking");
	return (0);
}
