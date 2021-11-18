/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/18 10:27:08 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_meal(int *fork_idx, t_philo *philo, const suseconds_t origin)
{
	suseconds_t	now;

	now = get_time();
	while (get_time_gap(now) / 1000
		< philo->table->philo_life[time_to_eat])
		usleep(500);
	printf("%dms philosopher %d is eating\n", get_time_gap(origin) / 1000,
		philo->ph_idx);
	pthread_mutex_lock(&(philo->mutex));
	philo->table->forks[fork_idx[0]] = 0;
	philo->table->forks[fork_idx[1]] = 0;
	pthread_mutex_unlock(&(philo->mutex));
}

void	take_fork(int *fork_idx, t_philo *philo, const suseconds_t origin)
{
	pthread_mutex_lock(&(philo->mutex));
	philo->table->forks[fork_idx[0]] = 1;
	philo->table->forks[fork_idx[1]] = 1;
	pthread_mutex_unlock(&(philo->mutex));
	printf("%dms philosopher %d has take a fork\n",
		get_time_gap(origin) / 1000, philo->ph_idx);
}

t_bool	go_to_eat(t_philo *philo, const suseconds_t origin)
{
	int			fork_idx[2];
	suseconds_t	now;

	fork_idx[0] = philo->ph_idx - 1;
	if (philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		fork_idx[1] = 0;
	else
		fork_idx[1] = philo->ph_idx;
	now = get_time();
	while (get_time_gap(now) < philo->table->philo_life[time_to_die])
	{
		if (!philo->table->forks[fork_idx[0]]
			&& !philo->table->forks[fork_idx[1]])
		{
			take_fork(fork_idx, philo, origin);
			have_meal(fork_idx, philo, origin);
			return (true);
		}
		else
			usleep(100);
	}
	return (false);
}

// t_bool	go_to_sleep(t_table *table, const suseconds_t origin)
// {

// }

// t_bool	go_to_thinking(t_table *table, const suseconds_t origin)
// {

// }
