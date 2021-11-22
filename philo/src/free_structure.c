/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:04:10 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/22 12:11:57 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_table(t_table **table)
{
	t_table	*to_free;
	int		err;

	to_free = *table;
	free(to_free->philo_life);
	err = pthread_mutex_destroy(&to_free->mutex);
	if (err)
		ft_print_syserr(err, false);
	free(*table);
	*table = NULL;
}

void	free_philo(t_philo *philo)
{
	int	err;

	err = pthread_mutex_destroy(philo->right);
	if (err)
		ft_print_syserr(err, false);
	else
		free(philo->right);
}

void	free_n_philo(t_philo **philo, int idx)
{
	while (idx--)
		free_philo(&philo[0][idx]);
	free(*philo);
	*philo = NULL;
}

void	free_memory(t_philo *philo, pthread_t *tid)
{
	int	cnt;

	cnt = philo->table->philo_life[number_of_philosopers];
	free(tid);
	free_table(&philo->table);
	free_n_philo(&philo, cnt);
}
