/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:25 by jberay            #+#    #+#             */
/*   Updated: 2024/02/23 09:14:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)

{
	t_data		data;

	if (argc < 5 || argc > 6)
		return (ret_error(E_ARGS, &data));
	if (check_input(argv))
		return (ret_error(E_ARGS, &data));
	if (check_args(&data, argv))
		return (ret_error(E_ARGS, &data));
	init_data(&data);
	if (to_malloc(&data))
		return (ret_error(E_MALLOC, &data));
	set_forks(&data);
	init_philos(&data);
	if (start_threads(&data))
		return (1);
	return (ret_error(NO_ERROR, &data));
}
