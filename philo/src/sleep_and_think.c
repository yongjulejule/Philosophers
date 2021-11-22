/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:37:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/22 13:34:23 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
