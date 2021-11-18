/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:37:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/18 15:47:12 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_cqueue	*init_queue(t_philo *philo)
{
	t_cqueue	*queue;

	queue = ft_alloc(philo->table->philo_life[number_of_philosopers],
			sizeof(t_cqueue), 0);
	if (!queue)
		return (NULL);
}
