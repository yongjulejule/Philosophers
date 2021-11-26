/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:32:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/26 16:16:39 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*born_philo(void *arg)
{
	t_philo	*philo;
	int		cnt;

	philo = (t_philo *)arg;
	cnt = 0;
	if (philo->ph_idx % 2 == 0
		|| philo->ph_idx == philo->table->philo_life[number_of_philosopers])
		usleep((philo->table->philo_life[number_of_philosopers] * 100));
	while (philo->table->alive)
	{
		go_to_eat(philo, philo->table->clock);
		if (philo->table->philo_life[each_philosoper_must_eat] != -1)
		{
			cnt++;
			check_eat_count(philo, cnt);
		}
		go_to_sleep(philo, philo->table->clock);
		go_to_think(philo, philo->table->clock);
	}
	return (arg);
}

t_bool	exit_philosopher(t_philo *philo, pthread_t *tid, int cnt)
{
	int	idx;
	int	err;

	idx = 0;
	err = 0;
	while (idx < cnt)
	{
		err = pthread_join(tid[idx++], NULL);
		if (err)
			return (ft_print_syserr(err, false));
	}
	free_memory(philo, tid);
	return (true);
}

static void	dead(t_philo *philo, int idx)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->alive)
		printf("\033[1;31m%ldms philosopher %d is died \033[0m \n",
			get_time_gap(philo->table->clock), philo[idx].ph_idx);
	philo->table->alive = false;
	pthread_mutex_unlock(&philo->table->mutex);
}

void	check_status(t_philo *philo)
{
	int		idx;
	int		cnt;
	int		ate;

	idx = 0;
	cnt = philo->table->philo_life[number_of_philosopers];
	ate = philo->table->philo_life[each_philosoper_must_eat];
	while (philo->table->alive && (cnt > philo->table->eat_cnt))
	{
		usleep(50);
		if ((philo[idx].status != eating && get_time_gap(philo[idx].hunger)
				>= philo->table->philo_life[time_to_die]))
			return (dead(philo, idx));
		idx++;
		if (idx >= cnt)
			idx = 0;
	}
	philo->table->alive = false;
}

t_bool	gen_philosopher(pthread_t *tid, void *(fp(void *arg)), t_philo *philo)
{
	int	err;

	philo->hunger = philo->table->clock;
	err = pthread_create(tid, NULL, fp, philo);
	if (err)
	{
		philo->table->alive = false;
		ft_print_syserr(err, EXIT_FAILURE);
		return (false);
	}
	return (true);
}
