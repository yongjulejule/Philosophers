/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:09:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/15 18:45:27 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"

#define NHASH 3
#define HASH(id) (((unsigned long)id) % NHASH)

struct foo	*fh[NHASH];
pthread_mutex_t	hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo
{
	int				f_count;
	pthread_mutex_t	f_lock;
	int				f_id;
	struct	foo		*f_next; /* protected by hashlock */
	/* ... More stuff what u want ... */
};

/* Allocate the object */

struct foo	*foo_alloc(int id)
{
	struct foo	*fp;
	int			idx;

	fp = (struct foo *)malloc(sizeof(struct foo));
	if (!fp)
		return (NULL);
	fp->f_count = 1;
	fp->f_id = id;
	if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
	{
		free(fp);
		return (NULL);
	}
	idx = HASH(id);
	pthread_mutex_lock(&hashlock);
	fp->f_next = fh[idx];
	fh[idx] = fp;
	pthread_mutex_lock(&fp->f_lock);
	pthread_mutex_unlock(&hashlock);
	/* ... initialize your stuff ... */
	pthread_mutex_unlock(&fp->f_lock);
	return (fp);
}

/* Add a reference to the object */

void	foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

/* Find an existing object */

struct foo	*foo_find(int id)
{
	struct foo	*fp;

	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next)
	{
		if (fp->f_id == id)
		{
			foo_hold(fp);
			break ;
		}
	}
	pthread_mutex_unlock(&hashlock);
	return (fp);
}

/* Release a reference to the object */

void	foo_rele(struct foo *fp)
{
	struct foo	*tfp;
	int			idx;

	pthread_mutex_lock(&fp->f_lock);
	/* Last reference */
	if (fp->f_count == 1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		/* Need to recheck the condition */
		if (fp->f_count != 1)
		{
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return ;
		}
		/* Remove from list */
		idx = HASH(fp->f_id);
		tfp = fh[idx];
		if (tfp == fp)
			fh[idx] = fp->f_next;
		else
		{
			while (tfp->f_next != fp)
				tfp = tfp->f_next;
			tfp->f_next = fp->f_next;
		}
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else
	{
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}

int	main()
{
	int i = 31;
	struct foo *test;

	while (i < 60)
	{
		test = foo_alloc(i);
		foo_find(i);
		foo_rele(test);
		i++;
	}
	foo_rele(test);
}