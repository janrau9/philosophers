/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:43:51 by jberay            #+#    #+#             */
/*   Updated: 2024/04/02 15:07:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	if (*str == '\0')
		return (-1);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str >= 0) && (*str == '-' || *str == '+'))
		str++;
	while ((*str >= '0' && *str <= '9'))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((long)result * sign);
}

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
			if (argv[i][j] == '+')
				j++;
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(t_data *data, char **argv)
{
	data->ph_count = ft_atoi(argv[1]);
	data->died = false;
	data->nbr_done = 0;
	data->thd_ph = NULL;
	data->forks = NULL;
	data->phs = NULL;
	data->time_to_die = (u_int64_t)ft_atoi(argv[2]);
	data->time_to_eat = (u_int64_t)ft_atoi(argv[3]);
	data->time_to_sleep = (u_int64_t)ft_atoi(argv[4]);
	data->start_time = get_time();
	if (argv[5])
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = -1;
	if (data->ph_count <= 0
		|| data->time_to_die < 0
		|| data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (E_ARGS);
	return (0);
}
