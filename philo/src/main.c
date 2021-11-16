/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 21:25:14 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	get_time_gap(suseconds_t origin)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec - origin);
}

void	*born_philo(void *arg)
{
	t_table			*table;
	struct timeval	tp;

	/* FIXME: DO WE NEED HADNLE ERROR? */
	table = (t_table *)arg;
	gettimeofday(&tp, NULL);
	printf("philosopher %d is born!\n", table->philo_nbr);
	printf("time gap is %d\n", get_time_gap(tp.tv_usec));
	go_to_eat();
	go_to_sleep();
	go_to_thinking();
	dead();
	return (arg);
}

t_bool	gen_philo_main(t_table table)
{
	int			err;
	pthread_t	*tid;

	tid = ft_alloc(table.philo_life[number_of_philosopers], sizeof(int), 0);
	if (!tid)
		return (false);
	while (table.philo_nbr < table.philo_life[number_of_philosopers])
	{
		err = pthread_create(&tid[table.philo_nbr], NULL, born_philo, &table);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			free(tid);
			return (false);
		}
		table.philo_nbr++;
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
	table->philo_nbr = 0;
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
