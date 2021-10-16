/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_basic_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:06:56 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/14 16:39:14 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread_test.h"
/* Mutex used to protect a data structure */

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct	foo	*fh[NHASH];
pthread_mutex_t	hashlock = PTHREAD_MUTEX_INITIALIZER;

struct	foo
{
	int				f_count;
	pthread_mutex_t	f_lock;
	int				f_id;
	struct	foo		*f_next; /* protected by hashlock */
	/* add blah blah stuff... */
};

/* don't need to lock when initialize memory cuz only ref exist here */
struct foo	*foo_alloc(int id)
{
	struct foo *fp;
	int			idx;

	fp = malloc(sizeof(struct foo));
	if (!fp)
		reutrn (NULL);
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
	pthread_mutex_lock(&fp->f_lock);
	pthread_mutex_unlock(&hashlock);
	/* Continue Initialization blah blah stuff... */
	pthread_mutex_unlock(&fp->f_lock);
	return (fp);
}

/* add a reference to the object */
void	foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

/* find an existing object */
struct	foo *foo_find(int id)
{
	struct foo	*fp;

	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASK(id)]; fp != NULL, fp = fp->f_next)
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

/* release a reference to the object */
void	foo_rele(struct foo *fp)
{
	struct foo	*tfp;
	int			idx;

	pthread_mutex_lock(&fp->f_lock);
	/* last reference */
	if (fp->f_count == 1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		/* need to recheck the condition NOTE : WHY?? */
		if (fp->f_count != 1)
		{
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return ;
		}
		/* remove from list */
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
		pthread_mutex_destory(&fp->f_lock);
		free(fp);
	}
	else
	{
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}