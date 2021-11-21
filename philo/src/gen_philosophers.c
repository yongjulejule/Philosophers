/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:32:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/21 14:27:47 by yongjule         ###   ########.fr       */
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
		usleep(100);
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
	int	cnt;

	cnt = philo->table->philo_life[number_of_philosopers];
	free(tid);
	free_table(&philo->table);
	free_n_philo(&philo, cnt);
}

static t_bool	exit_philosopher(t_philo *philo, pthread_t *tid)
{
	int	idx;
	int	err;

	idx = 0;
	err = 0;
	while (idx < philo->table->philo_life[number_of_philosopers])
	{
		err = pthread_join(tid[idx++], NULL);
		if (err)
		{
			ft_print_syserr(err, EXIT_FAILURE);
			return (false);
		}
	}
	free_memory(philo, tid);
	return (true);
}

static void	check_status(t_philo *philo)
{
	int		idx;
	t_table	*table;

	idx = 0;
	table = philo->table;
	while (philo->table->alive)
	{
		if (philo[idx].status != eating && get_time_gap(philo[idx].hunger)
			>= table->philo_life[time_to_die])
		{
			pthread_mutex_lock(&philo->table->mutex);
			if (table->alive)
				printf("\033[1;31m%ldms philosopher %d is died \033[0m \n",
					get_time_gap(table->clock), philo[idx].ph_idx);
			table->alive = false;
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		idx++;
		if (idx >= table->philo_life[number_of_philosopers])
			idx = 0;
	}
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
	idx = -1;
	while (++idx < philo->table->philo_life[number_of_philosopers])
	{
		philo[idx].hunger = philo->table->clock;
		err = pthread_create(&tid[idx], NULL, born_philo, &philo[idx]);
		if (err)
		{
			philo->table->alive = false;
			ft_print_syserr(err, EXIT_FAILURE);
			break ;
		}
	}
	check_status(philo);
	if (!exit_philosopher(philo, tid))
		return (false);
	return (true);
}
