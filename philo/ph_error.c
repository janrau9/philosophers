/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:45:29 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:34:11 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

	i = -1;
	while (++i < data->ph_count)
	{
		if (data->phs[i].mutex_last_meal.init)
			pthread_mutex_destroy(&data->phs[i].mutex_last_meal.mutex);
		if (data->phs[i].mutex_meals_eaten.init)
			pthread_mutex_destroy(&data->phs[i].mutex_meals_eaten.mutex);
		if (data->phs[i].mutex_state.init)
			pthread_mutex_destroy(&data->phs[i].mutex_state.mutex);
		if (data->phs[i].mutex_done.init)
			pthread_mutex_destroy(&data->phs[i].mutex_done.mutex);
		if (data->forks[i].init)
			pthread_mutex_destroy(&data->forks[i].mutex);
	}
	if (data->mutex_msg.init)
		pthread_mutex_destroy(&data->mutex_msg.mutex);
}

int	ret_error(t_error error, t_data *data)
{
	if (data)
	{
		destroy_mutex(data);
		if (data->thd_ph)
			free(data->thd_ph);
		if (data->forks)
			free(data->forks);
		if (data->phs)
			free(data->phs);
	}
	if (error != NO_ERROR)
	{
		write(2, "Error: ", 7);
		write(2, ft_strerror(error), ft_strlen(ft_strerror(error)));
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}
