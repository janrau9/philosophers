/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:14:25 by jberay            #+#    #+#             */
/*   Updated: 2024/02/28 12:01:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)

{
	t_data		data;

	if (argc < 5 || argc > 6)
		return (ret_error(E_ARGS, &data));
	if (check_input(argv))
		return (ret_error(E_ARGS, &data));
	if (check_args(&data, argv))
		return (ret_error(E_ARGS, &data));
	set_forks(&data);
	if (start_fork(&data))
		return (1);
	return (ret_error(NO_ERROR, &data));
}
