/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 17:58:11 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	is_digitstr(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	if (!*str)
		return (true);
	return (false);
}

t_bool	check_arg_validity(int argc, char **argv)
{
	int	flag;

	if (argc < 5 || argc > 6)
		return (false);
	flag = !is_digitstr(argv[1]) + !is_digitstr(argv[2]) + !is_digitstr(argv[3])
		+ !is_digitstr(argv[4]);
	if (argc == 6)
		flag += !is_digitstr(argv[5]);
	if (flag)
		return (false);
	return (true);
}
