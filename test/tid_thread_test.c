/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tid_thread_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:29:43 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/16 09:01:01 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

pthread_t	ntid;

void	printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	ntid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n[ntid is %lu]\n", s, (unsigned long) pid, (unsigned long)tid, (unsigned long)tid, (unsigned long)ntid);
}

void	*thr_fn(void *arg)
{
	printids("new thread: ");
	return (NULL);
}

int	main(void)
{
	int			err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	printf("first created thread id : %lu\n", (unsigned long)ntid);
	if (err != 0)
		strerror(err);
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	printf("secound created thread id : %lu\n", (unsigned long)ntid);
	if (err != 0)
		strerror(err);
	printids("main thread : ");
	printf("ntid in main is : %lu\n", (unsigned long)ntid);
	sleep (1);
	exit(EXIT_SUCCESS);
}
