/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:32:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/10 08:55:19 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_alloc(size_t count, size_t size, int c)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
	{
		is_err("Cannnot allocate memory", STDERR_FILENO, EXIT_FAILURE);
		return (NULL);
	}
	memset(tmp, c, count * size);
	return (tmp);
}
