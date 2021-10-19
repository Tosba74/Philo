/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/10 20:46:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	**init_fork(int nb_philo)
{
	int				i;
	pthread_mutex_t	**fork;

	i = -1;
	fork = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * nb_philo);
	if (!fork)
		return (NULL);
	while (++i < nb_philo)
	{
		fork[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!fork[i])
			return (NULL);
	}
	return (fork);
}

static t_philo	**init_phil(t_table *t, int nb_philo)
{
	int				i;
	t_philo			**phil;

	i = -1;
	phil = (t_philo **)malloc(sizeof(t_philo *) * nb_philo);
	if (!phil)
		return (NULL);
	while (++i < nb_philo)
	{
		phil[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!phil[i])
			return (NULL);
		phil[i]->t = t;
	}
	return (phil);
}

int	init(t_table *t, int nb_philo)
{
	t = malloc(sizeof(t_table));
	if (!t)
		return (-1);
	if (1 < nb_philo && nb_philo < 7)
		t->nb = nb_philo;
	t->philo = init_phil(t, nb_philo);
	if (!t->philo)
	{
		free(t);
		return (-1);
	}
	t->fork = init_fork(nb_philo);
	if (!t->fork)
	{
		free(t->philo);
		free(t);
		return (-1);
	}
	return (0);
}

static int	init_philo(t_philo *p, int i)
{
	p->id = i;
	p->state = 0;
	// if (pthread_mutex_init(&p->death, NULL))
	// 	return (-1);
	// pthread_create(&p->thread, NULL, &better_life, &p);
	// pthread_join(p->thread, NULL);
	return (0);
}

void	init_struct(t_table *t, char **av)
{
	int		i;

	i = -1;
	gettimeofday(&t->start, NULL);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		t->time_to_think = -1;
	else
		t->time_to_think = ft_atoi(av[5]);
	while (++i < (int)t->nb)
	{
		if (init_philo(t->philo[i], i) == -1)
			ft_err(t, "Mutex failed: ", 0);
		pthread_mutex_init(t->fork[i], NULL);
	}
}
