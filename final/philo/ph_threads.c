/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:30 by jberay            #+#    #+#             */
/*   Updated: 2024/04/08 09:17:23 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_loop(t_philo *ph)
{
	if (get_time() - read_last_meal(ph) > ph->data->time_to_die)
	{
		write_died(ph);
		mutex_lock(&ph->data->mutex_msg);
		printf("%lu %d %s\n", get_time() - ph->data->start_time,
			ph->id, "died");
		mutex_unlock(&ph->data->mutex_msg);
		return (1);
	}
	return (0);
}

static int	meal_loop(t_philo *ph)
{
	if (read_meals_eaten(ph) == ph->data->nbr_of_meals
		&& !read_done(ph))
	{
		write_done(ph);
		ph->data->nbr_done++;
	}
	if (ph->data->nbr_done == ph->data->ph_count)
	{
		write_died(ph);
		return (1);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_philo	*ph;
	t_data	*data;
	int		i;

	ph = (t_philo *)arg;
	data = ph->data;
	i = 0;
	while (1)
	{
		if (i == data->ph_count)
			i = 0;
		ph = &data->phs[i];
		if (death_loop(ph))
			break ;
		if (meal_loop(ph))
			break ;
		i++;
		usleep(1000);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		ft_usleep(ph->data->time_to_eat / 2);
	while (!read_died(ph))
	{
		if (eat_routine(ph))
			break ;
		if (sleep_routine(ph))
			break ;
		if (think_routine(ph))
			break ;
	}
	return (NULL);
}

int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(&data->thd_mon, NULL, &monitor, &data->phs[0]))
		return (ret_error(E_THREAD, data));
	while (++i < data->ph_count)
	{
		if (pthread_create(&data->thd_ph[i], NULL, &routine, &data->phs[i]))
			return (ret_error(E_THREAD, data));
	}
	if (pthread_join(data->thd_mon, NULL))
		return (ret_error(E_JOIN, data));
	i = -1;
	while (++i < data->ph_count)
		if (pthread_join(data->thd_ph[i], NULL))
			return (ret_error(E_JOIN, data));
	return (0);
}
