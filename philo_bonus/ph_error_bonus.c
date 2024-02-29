/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:45:29 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:09:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*ft_strerror(t_error error)
{
	if (error == E_ARGS)
		return ("Invalid arguments");
	else if (error == E_MALLOC)
		return ("Malloc failed");
	else if (error == E_THREAD)
		return ("Thread creation failed");
	else if (error == E_JOIN)
		return ("Thread join failed");
	else if (error == E_MUTEX)
		return ("Mutex creation failed");
	return (NULL);
}


int	ret_error(t_error error, t_data *data)
{
	if (data->sem_forks.init)
		sem_close(data->sem_forks.sem);
	if (data->sem_forks.init)
		sem_close(data->sem_print.sem);
	if (data->sem_dead.init)
		sem_close(data->sem_dead.sem);
	if (error != NO_ERROR)
	{
		printf("Error: %s\n", ft_strerror(error));
		return (0);
	}
	return (1);
}