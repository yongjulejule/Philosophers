/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 15:28:27 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*born_philo(void *arg)
{
	static int	philo_nbr = 0;

	printf("arg is %p\n", arg);
	printf("Philosopher %d is born!\n", philo_nbr);
	philo_nbr++;
	return (arg);
}

t_bool	gen_philo_main(int *philo_life)
{
	int			idx;
	int			err;
	pthread_t	*tid;

	tid = ft_alloc(philo_life[number_of_philosopers], sizeof(int), 0);
	if (!tid)
		return (false);
	idx = 0;
	while (idx < philo_life[number_of_philosopers])
	{
		err = pthread_create(&tid[idx], NULL, born_philo, NULL);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			free(tid);
			return (false);
		}
		idx++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int	*philo_life;

	if (!check_arg_validity(argc, argv))
		return (is_err("Invalid Arguments", STDERR_FILENO, EXIT_FAILURE));
	philo_life = get_philo_life(argc, argv);
	if (philo_life == NULL)
		return (EXIT_FAILURE);
	if (!gen_philo_main(philo_life))
		return (EXIT_FAILURE);
	usleep(10);
	return (EXIT_SUCCESS);
}
