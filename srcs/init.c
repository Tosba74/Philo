/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/26 22:06:42 by bmangin          ###   ########lyon.fr   */
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

// static int	init_philo(t_philo *p, int i)
// {
// 	p->id = i;
// 	p->state = 0;
// // 	// if (pthread_mutex_init(&p->death, NULL))
// // 	// 	return (-1);
// // 	// pthread_create(&p->thread, NULL, &better_life, &p);
// // 	// pthread_join(p->thread, NULL);
// 	return (0);
// }

void	init_struct(t_table *t, char **av)
{
	int		i;

	i = -1;
	t->nb = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&t->mutex, NULL);
	pthread_mutex_init(&t->state, NULL);
	if (!av[5])
		t->max_meal = -1;
	else
		t->max_meal = ft_atoi(av[5]);
	t->ready = 0;
	if (table.nb == 0 || table.time_to_die == 0 || table.time_to_eat == 0
		|| table.time_to_sleep == 0 || table.max_meal == 0)
			return (0);
	while (++i < t->nb)
	{
		t->philo[i].id = i;
		t->philo[i].state = 0;
		pthread_mutex_init(&t->philo[i].death, NULL);
		t->philo[i].t = t;
		pthread_create(&t->philo[i].thread, NULL, better_life, &t->philo[i]);
		pthread_mutex_init(&t->fork[i], NULL);
	}
	sleep(5);
	gettimeofday(&t->start, NULL);
	t->lm_time = get_time_ms();
}
