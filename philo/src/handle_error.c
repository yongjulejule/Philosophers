/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:06:10 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 15:23:16 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	ft_print_syserr(int err_nbr, int exit_status)
{
	if (!err_nbr)
		return (is_err("Not Error", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EAGAIN)
		return (is_err("Resource tempoaraily unavailable",
				STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EPERM)
		return (is_err("Operation not permitted", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EINVAL)
		return (is_err("Invalid argument", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == ESRCH)
		return (is_err("No such thread", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EDEADLK)
		return (is_err("Deadlock was detected", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EFAULT)
		return (is_err("Bad address", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == ENOMEM)
		return (is_err("Cannot allocate memory", STDERR_FILENO, EXIT_FAILURE));
	if (err_nbr == EBUSY)
		return (is_err("Mutex is locked", STDERR_FILENO, EXIT_FAILURE));
}

int	is_err(char *err_msg, int fd, int exit_status)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	return (exit_status);
}
