/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:13:51 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 10:02:30 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_data *data, int i)
{
	char	*sem_name;

	data->ph.id = i + 1;
	sem_name = ft_strjoin(SEM_NAME, ft_itoa(i));
	if (sem_name == NULL)
		exit(E_MALLOC);
	sem_unlink(sem_name);
	data->ph.sem.sem = sem_open(sem_name, O_CREAT, 0644, 1);
	if (data->ph.sem.sem == SEM_FAILED)
	{
		printf("Error: sem_open\n");
	}
}

void	set_forks(t_data *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	data->sem_forks.sem = sem_open(SEM_FORK, O_CREAT, 0644, data->ph_count);
	if (data->sem_forks.sem == SEM_FAILED)
	{
		printf("Error: sem_open\n");
	}
	data->sem_print.sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->sem_print.sem == SEM_FAILED)
	{
		printf("Error: sem_open\n");
	}
}


