/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:06:10 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 16:09:05 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	cnt;

	cnt = 0;
	if (str)
		return (cnt);
	while (*(str + cnt))
		cnt++;
	return (cnt);
}

int	is_err(char *err_msg, int fd, int exit_status)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	return (exit_status);
}
