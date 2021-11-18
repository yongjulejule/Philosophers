/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:43:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/18 16:20:55 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	*get_philo_life(int argc, char **argv)
{
	int	*philo_life;
	int	idx;

	idx = 0;
	philo_life = ft_alloc(5, sizeof(int), -1);
	if (!philo_life)
		return (NULL);
	while (idx < argc - 1)
	{
		philo_life[idx] = ft_atoui(argv[idx + 1]);
		if (philo_life[idx] == ERR)
		{
			is_err("Arguments is out of range", STDERR_FILENO, 0);
			return (NULL);
		}
		idx++;
	}
	if (philo_life[number_of_philosopers] == 0)
	{
		is_err("At least one Philosopher need", STDERR_FILENO, 0);
		return (NULL);
	}
	return (philo_life);
}

static t_table	*get_table_info(int *philo_life, int *forks)
{
	t_table	*table;

	table = ft_alloc(1, sizeof(t_table), 0);
	if (!table)
		return (NULL);
	table->philo_life = philo_life;
	table->forks = forks;
	table->alive = true;
	return (table);
}

static t_philo	*get_philo_data(t_table *table)
{
	t_philo	*philo;
	int		err;
	int		idx;

	philo = ft_alloc(table->philo_life[number_of_philosopers],
			sizeof(t_philo), 0);
	if (!philo)
		return (NULL);
	idx = 0;
	while (idx < table->philo_life[number_of_philosopers])
	{
		philo[idx].ph_idx = idx + 1;
		philo[idx].table = table;
		err = pthread_mutex_init(&(philo[idx].mutex), NULL);
		if (err)
		{
			ft_print_syserr(err, false);
			return (NULL);
		}
		idx++;
	}
	return (philo);
}

t_bool	get_info(int argc, char *argv[], t_philo **philo)
{
	int		*philo_life;
	int		*forks;
	t_table	*table;

	philo_life = get_philo_life(argc, argv);
	if (philo_life == NULL)
		return (false);
	forks = ft_alloc(philo_life[number_of_philosopers], sizeof(int), 0);
	if (!forks)
		return (false);
	table = get_table_info(philo_life, forks);
	if (!table)
		return (false);
	*philo = get_philo_data(table);
	if (!*philo)
		return (false);
	return (true);
}

t_bool	get_waiter(t_waiter *waiter, t_philo *philo)
{
	int	cnt;
	int	idx;

	cnt = philo->table->philo_life[number_of_philosopers];
	waiter->stat = ft_alloc(cnt, sizeof(t_status), nothing);
	if (!waiter->stat)
		return (false);
	waiter->queue = ft_alloc(3, sizeof(t_cqueue), 0);
	if (!waiter->queue)
		return (false);
	idx = 0;
	while (idx < 3)
	{
		waiter->queue[idx].queue = ft_alloc(cnt, sizeof(int), 0);
		if (!waiter->queue[idx].queue)
			break ;
		idx++;
	}
	while (idx >= 0 && idx < 3)
		free(waiter->queue[idx--].queue);
	if (idx == 3)
		return (true);
	else
		return (false);
}
