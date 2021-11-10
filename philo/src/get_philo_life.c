/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_life.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:43:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/10 09:18:49 by yongjule         ###   ########.fr       */
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

int	*get_philo_life(int argc, char **argv)
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
