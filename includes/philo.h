/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:26:56 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/04 17:26:58 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# include <errno.h>
# define ENOMEM 12
# define E2BIG 7
# define EINVAL 22
# define EAGAIN 35
# define EINVAL 22
# define EFAULT 14
# define ENOSYS 78
# define EAGAIN 35
# define EEXIST 17
# define ENFILE 23
# define EMFILE 24
# define EDEADLK 11
# define ENAMETOOLONG 63
# define EACCES 13

typedef struct timeval		t_timeval;

typedef struct s_err
{
	int		err;
	char	*strerror;
}	t_err;

typedef struct s_philo
{
	int					id;
	int					meals;
	long long			last_meal;
	int					fleft;
	int					fright;
	pthread_t			thread;
	struct s_table		*t;
}	t_philo;

typedef struct s_table
{
	int					nb;
	int					all_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meal;
	int					dead;
	int					ready;
	long long			start;
	t_timeval			time;
	t_philo				*philo;
	pthread_mutex_t		*death;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*speaker;
}	t_table;

int			init(t_table *t, int nb_philo);
void		init_struct(t_table *t, char **av);
void		acc_sleep(long long check);
int			compare_time(long long time);
long long	get_time(void);

int			ft_atoi(const char *str);
void		ft_swap(int *a, int *b);
void		ft_putnbr(long long n);
void		ft_putstr_fd(char *str, int fd);
void		ft_err(t_table *t, char *s, int err);

void		*better_life(void *arg);
void		phil_sleep(t_philo *p);
void		think(t_philo *p);
void		eat(t_philo *p);

int			msg_err(char *s1, char *s2, int ret);
void		free_struct(t_table *table);

void		print_table(t_table *t);
void		print_philo(t_philo *p);
void		say_me(t_table *t, int id, char *s);

#endif
