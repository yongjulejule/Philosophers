/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:32:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/19 16:26:37 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoui(char *str)
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

void	*ft_alloc(size_t count, size_t size, int c)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
	{
		ft_print_syserr(ENOMEM, EXIT_FAILURE);
		return (NULL);
	}
	memset(tmp, c, count * size);
	return (tmp);
}

size_t	ft_strlen(char *str)
{
	size_t	cnt;

	cnt = 0;
	if (!str)
		return (cnt);
	while (*(str + cnt))
		cnt++;
	return (cnt);
}

suseconds_t	get_time_gap(const suseconds_t origin)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec - origin);
}

suseconds_t	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec);
}
