/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:25 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/26 11:17:10 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	have_meal(t_philo *philo, const time_t origin)
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
	philo->hunger = get_time();
	while (get_time_gap(now) < philo->table->philo_life[time_to_eat])
	{
		if (philo->table->alive)
			usleep(500);
		else
			return ;
	}
}

static t_bool	get_forks(t_philo *philo, const time_t origin, int status)
{
	if (philo->table->alive)
	{
		printf("%ldms philosopher %d has taken a fork\n",
			get_time_gap(origin), philo->ph_idx);
		pthread_mutex_unlock(&philo->table->mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(&philo->table->mutex);
		if (status == RIGHT)
			pthread_mutex_unlock(philo->right);
		return (false);
	}
}

void	go_to_eat(t_philo *philo, const time_t origin)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->table->mutex);
	if (!get_forks(philo, origin, LEFT))
		return ;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->table->mutex);
	if (!get_forks(philo, origin, RIGHT))
		return ;
	pthread_mutex_unlock(&philo->table->mutex);
	if (philo->table->alive)
		have_meal(philo, origin);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*go_to_eat_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%ldms philosopher %d has take a fork\n",
		get_time_gap(philo->table->clock), philo->ph_idx);
	while (philo->table->alive)
		;
	return (arg);
}

void	check_eat_count(t_philo *philo, int cnt)
{
	if (philo->table->philo_life[each_philosoper_must_eat] == cnt)
	{
		pthread_mutex_lock(&philo->table->mutex);
		philo->table->eat_cnt++;
		pthread_mutex_unlock(&philo->table->mutex);
	}
}
