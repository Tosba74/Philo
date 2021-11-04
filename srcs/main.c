/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:57:41 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/04 17:27:15 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*better_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->t->ready)
		;
	p->last_meal = p->t->start;
	while (!p->t->dead)
	{
		eat(p);
		p->meals++;
		if (p->meals == p->t->max_meal && p->t->nb > 1)
			p->t->all_eat++;
		if (p->t->all_eat == p->t->nb || p->t->nb == 1 || p->t->dead)
			return (NULL);
		phil_sleep(p);
		if (p->t->all_eat == p->t->nb || p->t->dead)
			return (NULL);
		think(p);
	}
	return (NULL);
}

static void	start_time(t_table *t)
{
	gettimeofday(&t->time, NULL);
	t->start = get_time();
	t->ready = 1;
}

static void	check_life(t_table *t)
{
	int	i;

	start_time(t);
	while (!t->dead && t->all_eat != t->nb)
	{
		i = 0;
		while (i < t->nb)
		{
			pthread_mutex_lock(&t->death[i]);
			if (compare_time(t->philo[i].last_meal) > t->time_to_die
				&& t->all_eat != t->nb)
			{
				t->dead = 1;
				say_me(t, i, "is dead");
				pthread_mutex_unlock(&t->death[i]);
				return ;
			}
			pthread_mutex_unlock(&t->death[i]);
			i++;
		}
	}
	usleep(50);
}

int	main(int ac, char **av)
{
	int			i;
	int			nb_philo;
	t_table		table;

	i = -1;
	nb_philo = ft_atoi(av[1]);
	table = (t_table){};
	if (ac > 6)
		return (msg_err("Arg: ", "Argument list too long\n", 7));
	if (ac < 5)
		return (msg_err("Arg: ", "Argument list too short\n", 7));
	if (nb_philo < 1)
		return (msg_err("Arg: ", "Invalid argument!\n", 22));
	else
		if (init(&table, nb_philo) == -1)
			return (msg_err("Malloc failed: ", "Insufficient memory!\n", 22));
	init_struct(&table, av);
	check_life(&table);
	while (++i < table.nb)
		if (table.philo[i].thread)
			pthread_join(table.philo[i].thread, NULL);
	free_struct(&table);
	return (0);
}
