/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:30 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 08:59:13 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	loop_monitor(int i, t_philo *ph)
{
	while (++i < ph->data->ph_count)
	{
		ph = &ph->data->phs[i];
		if (get_time() - get_last_meal(ph) > \
			get_mutex_time(ph, TIME_TO_DIE))
		{
			set_state(ph, DEAD);
			display_msg(ph, "died");
			return (1);
		}
		if (get_meals_eaten(ph) == get_mutex_flag(ph, NBR_OF_MEALS)
			&& read_i_am_done(ph) == false)
		{
			write_i_am_done(ph, true);
			set_done(ph);
		}
		if (get_mutex_flag(ph, DONE) == get_mutex_flag(ph, PH_COUNT))
		{
			set_someone_died(ph, true);
			return (1);
		}
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
	while (!get_mutex_flag(ph, SOMEONE_DIED))
	{
		i = -1;
		if (loop_monitor(i, ph))
			break ;
	}
	i = -1;
	while (++i < ph->data->ph_count)
	{
		set_state(&data->phs[i], DEAD);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		ft_usleep(ph->data->time_to_eat / 2);
	while (!check_state(ph, DEAD))
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
	if (pthread_create(&data->thread_mon, NULL, &monitor, &data->phs[0]))
		return (ret_error(E_THREAD, data));
	while (++i < data->ph_count)
	{
		if (pthread_create(&data->thread_ph[i], NULL, &routine, &data->phs[i]))
			return (ret_error(E_THREAD, data));
	}
	if (pthread_join(data->thread_mon, NULL))
		return (ret_error(E_JOIN, data));
	i = -1;
	while (++i < data->ph_count)
		pthread_join(data->thread_ph[i], NULL);
	return (0);
}
