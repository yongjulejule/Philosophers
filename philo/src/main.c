/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:37:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/19 17:40:40 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
}

int	main(int argc, char **argv)
{
	if (!check_arg_validity(argc, argv))
		return (EXIT_FAILURE);
}