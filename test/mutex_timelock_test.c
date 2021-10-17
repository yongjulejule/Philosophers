/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_timelock_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:19:35 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/17 08:51:58 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

int	main(void)
{
	int				err;
	struct timespec	tout;
	struct tm		*tmp;
	char			buf[64];
	pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	printf("mutex is locked");
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);
	tout.tv_sec += 10; /* 10 seconds from now */
	/* Caution : this could be lead to deadlock */
	err = pthread_mutex_timelock(&lock, &tout);
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "&r", tmp);
	printf("the time is now %s\n", buf);
	if (!err)
		printf("mutex lockec again!\n");
	else
		printf("can't lock mutex again: %s\n", strerror(err));
	exit(0);
}
