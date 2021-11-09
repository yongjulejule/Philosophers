/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:38:17 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/09 15:14:49 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define ERR -1
# define INT_MAX 2147483647

typedef enum e_bool
{
	false = 0,
	true,
}	t_bool;

typedef struct s_life
{
	int	number_of_philosopers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosoper_must_eat;
}	t_life;

int		is_err(char *err_msg, int fd, int exit_status);
size_t	ft_strlen(char *str);
t_bool	is_digitstr(char *str);
t_bool	check_arg_validity(int argc, char **argv);

#endif