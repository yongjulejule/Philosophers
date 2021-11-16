/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:38:17 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 15:29:36 by yongjule         ###   ########.fr       */
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

# define INT_MAX 2147483647
# define ERR -1

/* System Errno */

# define EAGAIN 35
# define EPERM 1
# define EINVAL 22
# define ESRCH 3
# define EDEADLK 11
# define EFAULT 11
# define ENOMEM 12
# define EBUSY 16

typedef enum e_bool
{
	false = 0,
	true,
}	t_bool;

typedef enum e_life
{
	number_of_philosopers,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	number_of_times_each_philosoper_must_eat,
}	t_life;

int		is_err(char *err_msg, int fd, int exit_status);
size_t	ft_strlen(char *str);
t_bool	check_arg_validity(int argc, char **argv);
void	*ft_alloc(size_t count, size_t size, int c);
int		*get_philo_life(int argc, char **argv);
int		ft_print_syserr(int err_nbr, int exit_status);

#endif