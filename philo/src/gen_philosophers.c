/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:32:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/20 15:39:10 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* FIXME: DO WE NEED HADNLE ERROR? */
static void	*born_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ph_idx % 2 == 0 || philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		usleep(1000);
	while (philo->table->alive)
	{
		if (philo->table->philo_life[number_of_philosopers] != 1)
			go_to_eat(philo, philo->table->clock);
		if (philo->table->alive)
			go_to_sleep(philo, philo->table->clock);
		if (philo->table->alive)
			go_to_think(philo, philo->table->clock);
	}
	return (arg);
}

t_bool	philo_main(t_philo *philo)
{
	int				err;
	pthread_t		*tid;
	int				idx;

	tid = ft_alloc(philo->table->philo_life[number_of_philosopers],
			sizeof(int), 0);
	if (!tid)
		return (false);
	philo->table->clock = get_time();
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
	{
		err = pthread_join(tid[idx++], NULL);
		if (err)
			ft_print_syserr(err, EXIT_FAILURE);
		return (false);
	}
	return (true);
}
