/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_structure_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:42:52 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/13 17:38:44 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

struct foo	{
	int a, b, c, d;
};

void	printfoo(const char	*s, const struct foo *fp)
{
	printf("%s", s);
	printf("	structure at 0x%lx\n", (unsigned long)fp);
	printf("	foo.a = %d\n", fp->a);	
	printf("	foo.b = %d\n", fp->b);	
	printf("	foo.c = %d\n", fp->c);	
	printf("	foo.d = %d\n", fp->d);	
}

void	*thr_fn1(void *arg)
{
	struct	foo	foo = {1, 2, 3, 4};
	
	printfoo("thread 1:\n", &foo);
	pthread_exit((void	*)&foo);
}

void	*thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	pthread_exit((void *)0);
}

int	main(void)
{
	int		err;
	pthread_t	tid_1;
	pthread_t	tid_2;
	struct foo	*fp;
	
	strerror(0);
	err = pthread_create(&tid_1, NULL, thr_fn1, NULL);
	if (!err)
		strerror(err);
	printf("before join 1 fp is %p\n", fp);
	err = pthread_join(tid_1, (void *)&fp);
	printf("err is %d\n", err);
	if (!err)
		strerror(err);
	printf("before join 2 fp is %p\n", fp);
	fp = NULL;
	printf("after join and init fp is %p\n", fp);
	err = pthread_join(tid_1, (void *)&fp);
	printf("before join 3 fp is %p\n", fp);
	errno = err;
	printf("errno is %d\n", errno);
	if (err)
		perror("!!!!!!ERROR!!!!!!!!!");
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid_2, NULL, thr_fn2, NULL);
	if (!err)
		strerror(err);
	printf("after pthread create, its status is %d\n", err);
	err = pthread_detach(tid_2);
	if (!err)
		strerror(err);
	printf("after pthread detach, its status is %d\n", err);
	err = pthread_join(tid_2, (void *)&fp);
	printf("after pthread join, its status is (should be error!) %d\n", err);
	perror(strerror(err));
	sleep(1);
	printfoo("parent : \n", fp);
	return (EXIT_SUCCESS);
}