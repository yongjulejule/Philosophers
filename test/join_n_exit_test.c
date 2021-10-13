/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_n_exit_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:57:53 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/13 14:40:59 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

pthread_t	tid;

void	*thr_fn_1(void *arg)
{
	// sleep (1);
	printf("thread 1 returning, after sleeping 1 sec\n");
	printf("tid is %#lx", (unsigned long)tid);
	// pthread_kill(tid, SIGBUS);
	return ((void *)1);
}

void	*thr_fn_2(void *arg)
{
	int	*boom;
	
	boom = malloc(200);
	printf("thread 2 exiting after 5 sec\n");
	// sleep(5);
	printf("boom : %p\n", boom);
	pthread_exit((void *)boom);
	// return ((void *)boom);
}

int	main(void)
{
	int		err;
	pthread_t	tid_1;
	pthread_t	tid_2;
	void		*tret;
	int			*boom;
	
	err = pthread_create(&tid_1, NULL, thr_fn_1, NULL);
	if (!err)
		strerror(err);
	err = pthread_create(&tid, NULL, thr_fn_2, NULL);
	tid_2 = tid;
	if (!err)
		strerror(err);
	err = pthread_join(tid_1, &tret);
	if (!err)
		strerror(err);
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid_2, &tret);
	printf("%p\n", tret);
	if (!err)
		strerror(err);
	printf("pthread 2 exit code %ld\n", (long)tret);
	/* Wow This is work! As you know, we can free if we have address haha. */
	boom = err;
	free(boom);
	exit(EXIT_SUCCESS);
}