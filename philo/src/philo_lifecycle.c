/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/17 20:22:01 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	get_time_gap(const suseconds_t origin)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec - origin);
}

t_bool	toggle_fork(t_philo *philo, int *fork_idx, int state)
{
	int	err;

	err = pthread_mutex_lock(&(philo->mutex));
	if (err)
		return (ft_print_syserr(err, false));
	philo->table->forks[fork_idx[0]] = state;
	philo->table->forks[fork_idx[1]] = state;
	err = pthread_mutex_unlock(&(philo->mutex));
	if (err)
		return (ft_print_syserr(err, false));
	return (true);
}

t_bool	go_to_eat(t_philo *philo, const suseconds_t origin)
{
	int	fork_idx[2];

	fork_idx[0] = philo->ph_idx - 1;
	if (philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		fork_idx[1] = 0;
	else
		fork_idx[1] = philo->ph_idx;
	if (!philo->table->forks[fork_idx[0]] && !philo->table->forks[fork_idx[1]])
	{
		// if (!toggle_fork(philo, fork_idx, 1))
		// 	return (false);
		pthread_mutex_lock(&(philo->mutex));
		philo->table->forks[fork_idx[0]] = 1;
		philo->table->forks[fork_idx[1]] = 1;
		printf("%dms philosopher %d has take a fork\n",
			get_time_gap(origin) / 1000, philo->ph_idx);
		while (get_time_gap(origin) / 1000
			< philo->table->philo_life[time_to_eat])
			usleep(500);
		printf("%dms philosopher %d is eating\n", get_time_gap(origin) / 1000,
			philo->ph_idx);
		philo->table->forks[fork_idx[0]] = 0;
		philo->table->forks[fork_idx[1]] = 0;
		pthread_mutex_unlock(&(philo->mutex));
		// if (!toggle_fork(philo, fork_idx, 0))
		// 	return (false);
	}
	return (true);
}

// t_bool	go_to_sleep(t_table *table, const suseconds_t origin)
// {

// }

// t_bool	go_to_thinking(t_table *table, const suseconds_t origin)
// {

// }
