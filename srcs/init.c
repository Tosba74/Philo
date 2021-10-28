/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/28 17:00:15 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_table *t, int nb_philo)
{
	if (1 < nb_philo)
		t->nb = nb_philo;
	t->philo = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (!t->philo)
		return (-1);
	t->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!t->fork)
	{
		free(t->philo);
		return (-1);
	}
	return (0);
}

static void	init_philo(t_table *t)
{
	int		i;

	i = -1;
	while (++i < t->nb)
	{
		t->philo[i].id = i;
		t->philo[i].frigth = i;
		t->philo[i].fleft = (i - 1) % t->nb;
		t->philo[i].meals = i;
		pthread_mutex_init(&t->philo[i].death, NULL);
		t->philo[i].t = t;
		pthread_create(&t->philo[i].thread, NULL,
			better_life, &t->philo[i]);
		pthread_mutex_init(&t->fork[i], NULL);
	}
}

void	init_struct(t_table *t, char **av)
{
	int		i;

	i = -1;
	t->nb = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&t->state, NULL);
	pthread_mutex_init(&t->state, NULL);
	if (!av[5])
		t->max_meal = -1;
	else
		t->max_meal = ft_atoi(av[5]);
	t->ready = 0;
	t->is_dead = 0;
	t->nb_meal = 0;
	if (t->nb > 0 || t->time_to_die || t->time_to_eat
		|| t->time_to_sleep || t->max_meal)
		init_philo(t);
}
