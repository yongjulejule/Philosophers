/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:32:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 16:44:20 by yongjule         ###   ########.fr       */
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
