/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 09:53:45 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/17 10:46:23 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

/*
** if infinity loop in thread, limit is 2048
** recursive loop 1000 times, does not reach thread_max, about 200 threads can handle it
** Thread_stack max is 8192, but i don't know why
** it is better to put the condition in pthread_create than thread_cnt
** then I can make a more compatible program
*/

int	g_cnt = 0;

void	*fnc(void)
{
	g_cnt++;
	printf("cur g_cnt is %d\n", g_cnt);
	if (g_cnt == 1000)
	{
		g_cnt = 0;
		return(NULL);
	}
	fnc();
	return NULL;
}

int	main(void)
{
	int			cnt;
	int			err;
	pthread_t	tid;

	cnt = 1;
	err = pthread_create(&tid, NULL, fnc, NULL);
	while (!err)
	{
		err = pthread_create(&tid, NULL, fnc, NULL);
		cnt++;
		printf("cur cnt : %d\n", cnt);
	}
	printf("err : %s, errno is %d and cnt is %d\n", strerror(err), err, cnt);
}
