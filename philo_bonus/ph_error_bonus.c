/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:30:06 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 14:19:15 by jberay           ###   ########.fr       */
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
	else if (error == E_SEM)
		return ("Semaphore creation failed");
	else if (error == E_FORK)
		return ("Fork creation failed");
	return (NULL);
}

void	exit_error(t_error error, t_data *data)
{
	if (data->sem_forks.init)
		sem_close(data->sem_forks.sem);
	if (data->sem_print.init)
		sem_close(data->sem_print.sem);
	if (data->sem_full.init)
		sem_close(data->sem_full.sem);
	if (data->ph.sem.init)
		sem_close(data->ph.sem.sem);
	if (data->pid != NULL)
	{
		free(data->pid);
		data->pid = NULL;
	}
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_NAME);
	if (error != NO_ERROR)
	{
		printf("Error: %s\n", ft_strerror(error));
		exit(error);
	}
	exit (0);
}

void	exit_child(t_state state, t_data *data)
{
	if (data->sem_forks.init)
		sem_close(data->sem_forks.sem);
	if (data->sem_print.init)
		sem_close(data->sem_print.sem);
	if (data->sem_full.init)
		sem_close(data->sem_full.sem);
	if (data->ph.sem.init)
		sem_close(data->ph.sem.sem);
	if (data->pid != NULL)
	{
		free(data->pid);
		data->pid = NULL;
	}
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_NAME);
	exit(state);
}
