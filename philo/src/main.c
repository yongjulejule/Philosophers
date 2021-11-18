/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/18 15:26:24 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_waiter	waiter;

	if (!check_arg_validity(argc, argv))
		return (is_err("Invalid Arguments", STDERR_FILENO, EXIT_FAILURE));
	if (!get_info(argc, argv, &philo))
		return (EXIT_FAILURE);
	if (!get_waiter(&waiter, philo))
		return (EXIT_FAILURE);
	if (!philo_main(&waiter, philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
