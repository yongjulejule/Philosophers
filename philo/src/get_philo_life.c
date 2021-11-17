/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_life.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:43:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/17 17:06:36 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoui(char *str)
{
	long long	nbr;

	if (!str)
		return (ERR);
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		if (nbr > INT_MAX)
			return (ERR);
		str++;
	}
	return (nbr);
}

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
