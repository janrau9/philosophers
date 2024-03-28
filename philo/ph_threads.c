/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:30 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 10:24:53 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	loop_monitor(int i, t_philo *ph)
{
	u_int64_t	time;

	while (++i < ph->data->ph_count)
	{
		ph = &ph->data->phs[i];
		if (get_time() - read_last_meal(ph) > ph->data->time_to_die)
		{
			write_state(ph, DEAD);
			mutex_lock(&ph->data->mutex_msg);
			time = get_time() - ph->data->start_time;
			printf("%llu %d %s\n", time, ph->id, "died");
			mutex_unlock(&ph->data->mutex_msg);
			return (1);
		}
		if (read_meals_eaten(ph) == ph->data->nbr_of_meals
			&& !read_done(ph))
		{
			write_done(ph);
			ph->data->nbr_done++;
		}
		if (ph->data->nbr_done == ph->data->ph_count)
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
	while (1)
	{
		i = -1;
		if (loop_monitor(i, ph))
			break ;
	}
	i = -1;
	while (++i < ph->data->ph_count)
		write_state(&data->phs[i], DEAD);
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		ft_usleep(10);
	while (!read_state(ph, DEAD))
	{
		if (eat_routine(ph))
			break ;
		usleep(100);
		if (sleep_routine(ph))
			break ;
		usleep(100);
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
		pthread_detach(data->thd_ph[i]);
	return (0);
}
