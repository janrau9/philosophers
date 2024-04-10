/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:25 by jberay            #+#    #+#             */
/*   Updated: 2024/03/28 10:54:48 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)

{
	t_data		data;

	init_data(&data);
	if (argc < 5 || argc > 6)
		exit_error(E_ARGS, &data);
	if (check_input(argv))
		exit_error(E_ARGS, &data);
	check_args(&data, argv);
	set_forks(&data);
	start_fork(&data);
	exit_error(NO_ERROR, &data);
}
