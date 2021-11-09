/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_life.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:43:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 18:41:32 by yongjule         ###   ########.fr       */
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
	while (idx < argc - 1)
	{
		life_cycle[idx] = ft_atoui(argv[idx + 1]);
		if (life_cycle[idx] == ERR)
			return (NULL);
		printf("life_cycle[%d] is [%d]\n", idx, life_cycle[idx]);
		idx++;
	}
	return (life_cycle);
}
