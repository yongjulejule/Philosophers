/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_life.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:43:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 19:15:08 by yongjule         ###   ########.fr       */
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
	int	*life_cycle;
	int	idx;

	idx = 0;
	life_cycle = ft_alloc(5, sizeof(int), -1);
	if (!life_cycle)
		return (NULL);
	while (idx < argc - 1)
	{
		life_cycle[idx] = ft_atoui(argv[idx + 1]);
		if (life_cycle[idx] == ERR)
		{
			is_err("Arguments is out of range", STDERR_FILENO, 0);
			return (NULL);
		}
		printf("life_cycle[%d] is [%d]\n", idx, life_cycle[idx]);
		idx++;
	}
	return (life_cycle);
}
