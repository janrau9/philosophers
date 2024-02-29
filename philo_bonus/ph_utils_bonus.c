/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:15:15 by jberay            #+#    #+#             */
/*   Updated: 2024/02/28 12:02:10 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(const char *str)
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

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (0);
	return (tv.tv_sec * (u_int64_t)1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(500);
	}
}
