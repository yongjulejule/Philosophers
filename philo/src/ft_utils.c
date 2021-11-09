/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:32:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 15:32:25 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_alloc(int count, int size, int c)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	memset(tmp, c, count * size);
	return (tmp);
}

int	ft_atoui(char *str)
{
	long long	nbr;

	if (!str)
		return (ERR);
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr += *str;
		if (nbr > INT_MAX)
			return (ERR);
		nbr *= 10;
		str++;
	}
	return (nbr);
}
