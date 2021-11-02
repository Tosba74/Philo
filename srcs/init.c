/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/02 15:28:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb)
	{
		pthread_mutex_unlock(&table->fork[i]);
		pthread_mutex_destroy(&table->fork[i]);
		pthread_mutex_unlock(&table->death[i]);
		pthread_mutex_destroy(&table->death[i]);
	}
	pthread_mutex_unlock(table->speaker);
	pthread_mutex_destroy(table->speaker);
	if (table->philo)
		free(table->philo);
	if (table->fork)
		free(table->fork);
	if (table->death)
		free(table->death);
	if (table->speaker)
		free(table->speaker);
}

int	init(t_table *t, int nb_philo)
{
	t->philo = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (!t->philo)
		return (-1);
	t->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!t->fork)
	{
		free(t->philo);
		return (-1);
	}
	t->death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!t->death)
	{
		free(t->philo);
		free(t->fork);
		return (-1);
	}
	t->speaker = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!t->speaker)
	{
		free(t->philo);
		free(t->fork);
		free(t->death);
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
		t->philo[i].meals = 0;
		t->philo[i].fleft = i;
		t->philo[i].s_fork = i + 1;
		if (t->philo[i].s_fork == t->nb)
			t->philo[i].s_fork = 0;
		t->philo[i].t = t;
		pthread_mutex_init(&t->fork[i], NULL);
		pthread_mutex_init(&t->death[i], NULL);
		pthread_create(&t->philo[i].thread, NULL,
			better_life, &t->philo[i]);
	}
	pthread_mutex_init(t->speaker, NULL);
}

void	init_struct(t_table *t, char **av)
{
	int		i;

	i = -1;
	t->nb = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		t->max_meal = t->nb;
	else
		t->max_meal = ft_atoi(av[5]);
	t->power = OFF;
	if (t->nb > 0 || t->time_to_die || t->time_to_eat
		|| t->time_to_sleep || t->max_meal)
		init_philo(t);
}
