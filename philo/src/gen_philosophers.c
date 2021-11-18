/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:32:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/18 20:51:06 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* FIXME: DO WE NEED HADNLE ERROR? */
static void	*born_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->alive)
	{
		if (philo->table->philo_life[number_of_philosopers] != 1)
			philo->table->alive = go_to_eat(philo, philo->table->clock);
		// else
		// 	die();
		if (philo->table->alive)
		{
			// go_to_sleep(philo, philo->table->clock);
			// go_to_thinking(philo, philo->table->clock);
		}
		// else
		// 	die();
	}
	return (arg);
}

t_bool	philo_main(t_waiter *waiter, t_philo *philo)
{
	int				err;
	pthread_t		*tid;
	int				idx;
	struct timeval	tp;

	tid = ft_alloc(philo->table->philo_life[number_of_philosopers],
			sizeof(int), 0);
	if (!tid)
		return (false);
	gettimeofday(&tp, NULL);
	philo->table->clock = tp.tv_usec;
	idx = 0;
	while (idx < philo->table->philo_life[number_of_philosopers])
	{
		usleep(10);
		err = pthread_create(&tid[idx], NULL, born_philo, &philo[idx]);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			free(tid);
			return (false);
		}
		idx++;
	}
	idx = 0;
	while (idx < philo->table->philo_life[number_of_philosopers])
		pthread_join(tid[idx++], NULL);
	return (true);
}
