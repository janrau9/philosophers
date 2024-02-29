/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:43:51 by jberay            #+#    #+#             */
/*   Updated: 2024/02/29 08:29:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
				j++;
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(t_data *args, char **argv)
{
	args->ph_count = ft_atoi(argv[1]);
	args->time_to_die = (u_int64_t)ft_atoi(argv[2]);
	args->time_to_eat = (u_int64_t)ft_atoi(argv[3]);
	args->time_to_sleep = (u_int64_t)ft_atoi(argv[4]);
	args->start_time = get_time();
	args->ph.data = args;
	args->ph.id = -1;
	args->ph.last_meal = args->start_time;
	args->ph.state = THINKING;
	args->ph.meals_eaten = 0;
	args->ph.i_am_done = false;
	if (argv[5])
		args->nbr_of_meals = ft_atoi(argv[5]);
	else
		args->nbr_of_meals = -1;
	if (args->ph_count <= 0
		|| args->time_to_die < 0
		|| args->time_to_eat < 0
		|| args->time_to_sleep < 0)
		return (E_ARGS);
	return (0);
}
