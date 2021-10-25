/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/25 18:40:11 by bmangin          ###   ########lyon.fr   */
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
	gettimeofday(&t->start, NULL);
	t->nb = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		t->time_to_think = -1;
	else
		t->time_to_think = ft_atoi(av[5]);
	while (++i < t->nb)
	{
		printf("%d -- %d\n", i, t->nb);
		// if (init_philo(t->philo[i], i) == -1)
			// ft_err(t, "Mutex failed: ", 0);
		t->philo[i].id = i;
		t->philo[i].state = 0;
		t->philo[i].t = t;
		// if (pthread_mutex_init(t->fork[i], NULL) == -1)
		// 	ft_err(t, "Mutex failed: ", 0);
	}
}
