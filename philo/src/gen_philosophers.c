/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:32:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/20 17:07:10 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* FIXME: DO WE NEED HADNLE ERROR? */
static void	*born_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ph_idx % 2 == 0
		|| philo->ph_idx == philo->table->philo_life[number_of_philosopers])
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

/* TODO : destroy mutex, free philo structure, tid, free if fail to join */

static void	free_memory(t_philo *philo, pthread_t *tid)
{
	free(tid);
	philo->ph_idx = 1;
}

static t_bool	exit_philosopher(t_philo *philo, pthread_t *tid)
{
	int	idx;
	int	err;

	idx = 0;
	while (idx < philo->table->philo_life[number_of_philosopers])
	{
		err = pthread_join(tid[idx++], NULL);
		if (err)
			ft_print_syserr(err, EXIT_FAILURE);
		return (false);
	}
	free_memory(philo, tid);
	return (true);
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
		philo[idx].hunger = philo->table->clock;
		err = pthread_create(&tid[idx], NULL, born_philo, &philo[idx]);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			free(tid);
			return (false);
		}
		idx++;
	}
	if (!exit_philosopher(philo, tid))
		return (false);
	return (true);
}
