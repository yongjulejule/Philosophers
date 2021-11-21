/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/21 12:09:10 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_meal(int *fork_idx, t_philo *philo, const time_t origin)
{
	time_t	now;

	now = get_time();
	philo->status = eating;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->alive)
		printf("%ldms philosopher %d is eating\n", get_time_gap(origin),
			philo->ph_idx);
	else
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}	
	pthread_mutex_unlock(&philo->table->mutex);
	while (get_time_gap(now) < philo->table->philo_life[time_to_eat])
	{
		if (philo->table->alive)
			usleep(500);
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
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->alive)
		printf("%ldms philosopher %d has take a fork\n",
			get_time_gap(origin), philo->ph_idx);
	philo->table->forks[fork_idx[1]] = 1;
	if (philo->table->alive)
		printf("%ldms philosopher %d has take a fork\n",
			get_time_gap(origin), philo->ph_idx);
	else
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}	
	pthread_mutex_unlock(&philo->table->mutex);
}

void	go_to_eat(t_philo *philo, const time_t origin)
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
}

void	go_to_sleep(t_philo *philo, const time_t origin)
{
	time_t	now;

	now = get_time();
	philo->status = sleeping;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->alive)
		printf("%ldms philosopher %d is sleeping\n", get_time_gap(origin),
			philo->ph_idx);
	else
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}	
	pthread_mutex_unlock(&philo->table->mutex);
	while (philo->table->alive && get_time_gap(now)
		< philo->table->philo_life[time_to_sleep])
		usleep(500);
}

void	go_to_think(t_philo *philo, const time_t origin)
{
	philo->status = thinking;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->alive)
		printf("%ldms philosopher %d is thinking\n", get_time_gap(origin),
			philo->ph_idx);
	else
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}	
	pthread_mutex_unlock(&philo->table->mutex);
}
