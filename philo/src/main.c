/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/26 15:53:59 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_main(t_philo *philo)
{
	pthread_t		*tid;
	int				idx;

	tid = ft_alloc(philo->table->philo_life[number_of_philosopers],
			sizeof(int), 0);
	if (!tid)
		return (false);
	philo->table->clock = get_time();
	idx = 0;
	if (philo->table->philo_life[number_of_philosopers] == 1)
		idx += gen_philosopher(&tid[idx], go_to_eat_alone, &philo[idx]);
	else
	{
		while (idx < philo->table->philo_life[number_of_philosopers])
		{
			if (!gen_philosopher(&tid[idx], born_philo, &philo[idx]))
				break ;
			idx++;
		}
	}
	check_status(philo);
	if (!exit_philosopher(philo, tid, idx))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	if (!check_arg_validity(argc, argv))
		return (is_err("Invalid Arguments\n", STDERR_FILENO, EXIT_FAILURE));
	if (!get_info(argc, argv, &philo))
		return (EXIT_FAILURE);
	if (!philo_main(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
