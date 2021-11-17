/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/17 20:51:09 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	get_time_gap(const suseconds_t origin)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec - origin);
}

void	take_fork_n_eat(int *fork_idx, t_philo *philo, const suseconds_t origin)
{
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
}

t_bool	go_to_eat(t_philo *philo, const suseconds_t origin)
{
	int	fork_idx[2];

	fork_idx[0] = philo->ph_idx - 1;
	if (philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		fork_idx[1] = 0;
	else
		fork_idx[1] = philo->ph_idx;
	pthread_mutex_lock(&(philo->mutex));
	if (!philo->table->forks[fork_idx[0]] && !philo->table->forks[fork_idx[1]])
		take_fork_n_eat(fork_idx, philo, origin);
	pthread_mutex_unlock(&(philo->mutex));
	return (true);
}

// t_bool	go_to_sleep(t_table *table, const suseconds_t origin)
// {

// }

// t_bool	go_to_thinking(t_table *table, const suseconds_t origin)
// {

// }
