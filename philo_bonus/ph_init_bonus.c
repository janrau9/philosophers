/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:30:43 by jberay            #+#    #+#             */
/*   Updated: 2024/03/01 11:31:45 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_data *data, int i)
{
	char	*sem_name;

	data->ph.id = i + 1;
	sem_name = ft_strjoin(SEM_NAME, ft_itoa(i));
	if (sem_name == NULL)
		exit_error(E_MALLOC, data);
	sem_unlink(sem_name);
	data->ph.sem.sem = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(sem_name);
	set_last_meal(data);
	if (data->ph.sem.sem == SEM_FAILED)
		exit_error(E_SEM, data);
	data->ph.sem.init = true;
}

void	set_forks(t_data *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	data->sem_forks.sem = sem_open(SEM_FORK, O_CREAT, 0644, data->ph_count);
	if (data->sem_forks.sem == SEM_FAILED)
		exit_error(E_SEM, data);
	data->sem_forks.init = true;
	data->sem_print.sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->sem_print.sem == SEM_FAILED)
		exit_error(E_SEM, data);
	data->sem_print.init = true;
}

void	init_data(t_data *data)
{
	data->start_time = get_time();
	data->ph_count = 0;
	data->nbr_of_meals = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->pid = NULL;
	data->sem_forks.init = false;
	data->sem_print.init = false;
	data->sem_dead.init = false;
	data->ph.id = -1;
	data->ph.last_meal = data->start_time;
	data->ph.state = THINKING;
	data->ph.meals_eaten = 0;
	data->ph.i_am_done = false;
}
