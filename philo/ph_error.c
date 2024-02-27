/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:45:29 by jberay            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	destroy_mutex(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		if (data->mutex[i].init)
			pthread_mutex_destroy(&data->mutex[i].mutex);
	}
	i = -1;
	while (++i < data->ph_count)
	{
		if (data->forks[i].init)
			pthread_mutex_destroy(&data->forks[i].mutex);
	}
	j = -1;
	i = -1;
	while (++i < data->ph_count)
	{
		while (++j < 4)
		{
			if (data->phs[i].mutex[j].init)
				pthread_mutex_destroy(&data->phs[i].mutex[j].mutex);
		}
	}
}

int	ret_error(t_error error, t_data *data)
{
	destroy_mutex(data);
	if (data->thread_ph)
		free(data->thread_ph);
	if (data->forks)
		free(data->forks);
	if (data->phs)
		free(data->phs);
	if (error != NO_ERROR)
	{
		printf("Error: %s\n", ft_strerror(error));
		return (0);
	}
	return (1);
}
