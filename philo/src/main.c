/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/17 09:33:28 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_arg_validity(argc, argv))
		return (is_err("Invalid Arguments", STDERR_FILENO, EXIT_FAILURE));
	if (!get_info(argc, argv, &table))
		return (EXIT_FAILURE);
	if (!gen_philo_main(table))
		return (EXIT_FAILURE);
	usleep(10);
	return (EXIT_SUCCESS);
}
