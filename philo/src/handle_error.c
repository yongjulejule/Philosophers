/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:06:10 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/21 17:17:57 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_print_syserr(int err_nbr, int exit_status)
{
	if (!err_nbr)
		return (exit_status);
	else if (err_nbr == EAGAIN)
		return (is_err("Resource tempoaraily unavailable\n",
				STDERR_FILENO, exit_status));
	else if (err_nbr == EPERM)
		return (is_err("Operation not permitted\n", STDERR_FILENO, exit_status));
	else if (err_nbr == EINVAL)
		return (is_err("Invalid argument\n", STDERR_FILENO, exit_status));
	else if (err_nbr == ESRCH)
		return (is_err("No such thread\n", STDERR_FILENO, exit_status));
	else if (err_nbr == EDEADLK)
		return (is_err("Deadlock was detected\n", STDERR_FILENO, exit_status));
	else if (err_nbr == EFAULT)
		return (is_err("Bad address\n", STDERR_FILENO, exit_status));
	else if (err_nbr == ENOMEM)
		return (is_err("Cannot allocate memory\n", STDERR_FILENO, exit_status));
	else if (err_nbr == EBUSY)
		return (is_err("Mutex is locked\n", STDERR_FILENO, exit_status));
	else
		return (is_err("Undefined error occur\n", STDERR_FILENO, exit_status));
}

int	is_err(char *err_msg, int fd, int exit_status)
{
	write(fd, err_msg, ft_strlen(err_msg));
	return (exit_status);
}
