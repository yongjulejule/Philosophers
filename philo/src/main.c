/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 17:54:11 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*born_philo(void *arg)
{
	static int	philo_nbr = 1;

	printf("Philosopher %d is born!\n", philo_nbr);
	philo_nbr++;
	return (arg);
}

t_bool	gen_philo_main(t_table table)
{
	int			idx;
	int			err;
	pthread_t	*tid;

	tid = ft_alloc(table.philo_life[number_of_philosopers], sizeof(int), 0);
	if (!tid)
		return (false);
	idx = 0;
	while (idx < table.philo_life[number_of_philosopers])
	{
		err = pthread_create(&tid[idx], NULL, born_philo, &table);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			free(tid);
			return (false);
		}
		idx++;
	}
	table.forks[0] = 1;
	return (true);
}

t_bool	get_info(int argc, char *argv[], t_table *table)
{
	int	*philo_life;
	int	*forks;

	philo_life = get_philo_life(argc, argv);
	if (philo_life == NULL)
		return (false);
	forks = ft_alloc(philo_life[number_of_philosopers] + 1, sizeof(int), 0);
	if (!forks)
		return (false);
	table->philo_life = philo_life;
	table->forks = forks;
	return (true);
}

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
