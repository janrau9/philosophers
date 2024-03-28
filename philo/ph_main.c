/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:25 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 09:31:45 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_error		exit_code;

	if (argc < 5 || argc > 6)
		return (ret_error(E_ARGS, NULL));
	if (check_input(argv))
		return (ret_error(E_ARGS, NULL));
	if (check_args(&data, argv))
		return (ret_error(E_ARGS, &data));
	if (to_malloc(&data))
		return (ret_error(E_MALLOC, &data));
	if (init_mutexes(&data))
		return (ret_error(E_MUTEX, &data));
	if (init_philos(&data))
		return (ret_error(E_THREAD, &data));
	exit_code = start_threads(&data);
	if (exit_code != NO_ERROR)
		return (exit_code);
	return (ret_error(NO_ERROR, &data));
}
