/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/20 18:06:02 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_meal(int *fork_idx, t_philo *philo, const time_t origin)
{
	time_t	now;

	now = get_time();
	printf("%ldms philosopher %d is eating\n", get_time_gap(origin),
		philo->ph_idx);
	while (get_time_gap(now) < philo->table->philo_life[time_to_eat])
	{
		if (philo->table->alive)
			usleep(1);
		else
			return ;
	}
	philo->hunger = get_time();
	philo->table->forks[fork_idx[0]] = 0;
	philo->table->forks[fork_idx[1]] = 0;
}

void	take_fork(int *fork_idx, t_philo *philo, const time_t origin)
{
	philo->table->forks[fork_idx[0]] = 1;
	printf("%ldms philosopher %d has take a fork(left)\n",
		get_time_gap(origin), philo->ph_idx);
	philo->table->forks[fork_idx[1]] = 1;
	printf("%ldms philosopher %d has take a fork(right)\n",
		get_time_gap(origin), philo->ph_idx);
}

t_bool	go_to_eat(t_philo *philo, const time_t origin)
{
	int		fork_idx[2];

	fork_idx[LEFT] = philo->ph_idx - 1;
	if (philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		fork_idx[RIGHT] = 0;
	else
		fork_idx[RIGHT] = philo->ph_idx;
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	if (philo->table->alive)
		take_fork(fork_idx, philo, origin);
	if (philo->table->alive)
		have_meal(fork_idx, philo, origin);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (true);
}

t_bool	go_to_sleep(t_philo *philo, const time_t origin)
{
	time_t	now;

	now = get_time();
	if (philo->table->alive)
		printf("%ldms philosopher %d is sleeping\n", get_time_gap(origin),
			philo->ph_idx);
	else
		return (false);
	if (get_time_gap(philo->hunger) > philo->table->philo_life[time_to_die])
	{
		if (philo->table->alive)
			printf("%ldms philosopher %d is died\n", get_time_gap(origin),
				philo->ph_idx);
		philo->table->alive = false;
		return (false);
	}
	while (philo->table->alive && get_time_gap(now)
		< philo->table->philo_life[time_to_sleep])
		usleep(1);
	return (true);
}

t_bool	go_to_think(t_philo *philo, const time_t origin)
{
	if (get_time_gap(philo->hunger) > philo->table->philo_life[time_to_die])
	{
		if (philo->table->alive)
			printf("%ldms philosopher %d is died\n", get_time_gap(origin),
				philo->ph_idx);
		philo->table->alive = false;
		return (false);
	}
	if (philo->table->alive)
		printf("%ldms philosopher %d is thinking\n", get_time_gap(origin),
			philo->ph_idx);
	else
		return (false);
	return (true);
}
