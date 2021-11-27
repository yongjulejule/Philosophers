/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:38:17 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/27 14:20:06 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define ERR -1
# define LEFT 0
# define RIGHT 1

/* System Errno */

# define EAGAIN 35
# define EPERM 1
# define EINVAL 22
# define ESRCH 3
# define EDEADLK 11
# define EFAULT 11
# define ENOMEM 12
# define EBUSY 16

/* User Define Types */

typedef enum e_bool
{
	false = 0,
	true,
}	t_bool;

typedef enum e_life
{
	number_of_philosopers = 0,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	each_philosoper_must_eat,
}	t_life;

typedef enum e_status
{
	hunger = 0,
	eating,
	sleeping,
	thinking,
}	t_status;

/* User Define Structure */

typedef struct s_table
{
	time_t			clock;
	t_bool			alive;
	int				eat_cnt;
	int				*philo_life;
	pthread_mutex_t	mutex;
}	t_table;

typedef struct s_philo
{
	int				ph_idx;
	t_status		status;
	time_t			hunger;
	t_table			*table;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

/* FUNCTIONS */
/* Check Validity */

t_bool		check_arg_validity(int argc, char **argv);

/* Get Information */

t_bool		get_info(int argc, char *argv[], t_philo **philo);

/* Philosopher Life */

t_bool		gen_philosopher(pthread_t *tid,
				void *(fp(void *arg)), t_philo *philo);
t_bool		philo_main(t_philo *philo);
void		go_to_eat(t_philo *philo, const time_t origin);
void		*go_to_eat_alone(void *arg);
void		check_eat_count(t_philo *philo, int cnt);
void		go_to_sleep(t_philo *philo, const time_t origin);
void		go_to_think(t_philo *philo, const time_t origin);
time_t		get_time_gap(const time_t origin);
time_t		get_time(void);
void		check_status(t_philo *philo);
void		*born_philo(void *arg);
t_bool		exit_philosopher(t_philo *philo, pthread_t *tid, int cnt);

/* Utils */

int			is_err(char *err_msg, int fd, int exit_status);
size_t		ft_strlen(char *str);
void		*ft_alloc(size_t count, size_t size, int c);
int			ft_print_syserr(int err_nbr, int exit_status);
int			ft_atoui(char *str);
void		free_table(t_table **table);
void		free_n_philo(t_philo **philo, int nbr);
void		free_philo(t_philo *philo);
void		free_memory(t_philo *philo, pthread_t *tid);

#endif