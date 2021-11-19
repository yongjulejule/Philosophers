/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/19 12:59:58 yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_meal(int *fork_idx, t_philo *philo, const suseconds_t origin)
{
	suseconds_t	now;

	now = get_time();
	printf("%dms philosopher %d is eating\n", get_time_gap(origin) / 1000,
		philo->ph_idx);
	while (get_time_gap(now) / 1000
		< philo->table->philo_life[time_to_eat])
	{
		if (philo->table->alive)
			usleep(500);
		else
			return ;
	}
	philo->table->forks[fork_idx[0]] = 0;
	philo->table->forks[fork_idx[1]] = 0;
}

void	take_fork(int *fork_idx, t_philo *philo, const suseconds_t origin)
{
	philo->table->forks[fork_idx[0]] = 1;
	printf("%dms philosopher %d has take a fork(left)\n",
		get_time_gap(origin) / 1000, philo->ph_idx);
	philo->table->forks[fork_idx[1]] = 1;
	printf("%dms philosopher %d has take a fork(right)\n",
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
	if (get_time_gap(now) / 1000 > philo->table->philo_life[time_to_die])
	{
		if (philo->table->alive)
			printf("%dms philosopher %d is died\n", get_time_gap(origin) / 1000, philo->ph_idx);
		philo->table->alive = false;
		return (false);
	}
	pthread_mutex_lock(philo->left);
	printf("left %d \n", philo->ph_idx);
	pthread_mutex_lock(philo->right);
	printf("right%d \n", philo->ph_idx);
	if (philo->table->alive)
		take_fork(fork_idx, philo, origin);
	if (philo->table->alive)
		have_meal(fork_idx, philo, origin);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (true);
}

t_bool	go_to_sleep(t_philo *philo, const suseconds_t origin)
{
	suseconds_t	now;

	now = get_time();
	if (philo->table->alive)
		printf("%dms philosopher %d is sleeping\n", get_time_gap(origin) / 1000,
			philo->ph_idx);
	else
		return (false);
	while (philo->table->alive && get_time_gap(now) / 1000 < philo->table->philo_life[time_to_sleep])
		usleep(100);
	return (true);
}

t_bool	go_to_think(t_philo *philo, const suseconds_t origin)
{
	suseconds_t	now;

	now = get_time();
	while (get_time_gap(now) / 1000 < philo->table->philo_life[time_to_sleep])
		usleep(100);
	printf("%dms philosopher %d is sleeping\n", get_time_gap(origin) / 1000,
		philo->ph_idx);
	return (true);
}
