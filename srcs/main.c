/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:57:41 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/28 18:43:59y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void	eat(t_philo	*p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->t->fork[p->s_fork]);
		say_me(p->t, p->id, "take a fork!");
		pthread_mutex_lock(&p->t->fork[p->id]);
		say_me(p->t, p->id, "take a second fork!");
		pthread_mutex_lock(&p->t->death[p->id]);
	}
	else
	{
		pthread_mutex_lock(&p->t->fork[p->id]);
		say_me(p->t, p->id, "take a fork!");
		if (p->t->nb == 1)
			return ;
		pthread_mutex_lock(&p->t->fork[p->s_fork]);
		say_me(p->t, p->id, "take a second fork!");
		pthread_mutex_lock(&p->t->death[p->id]);
	}
	p->last_meal = get_time();
	say_me(p->t, p->id, "is eating");
	acc_sleep(p->t->time_to_eat);
	pthread_mutex_unlock(&p->t->fork[p->s_fork]);
	pthread_mutex_unlock(&p->t->fork[p->id]);
	pthread_mutex_unlock(&p->t->death[p->id]);
}

void	*better_life(void *arg)
{
	t_philo	*p;

	p = arg;
	while (!p->t->power)
		;
	p->last_meal = p->t->start;
	while (!p->t->is_dead)
	{
		eat(p);
		p->meals++;
		if (p->meals == p->t->max_meal && p->t->nb > 1)
			p->t->nb_meal++;
		if (p->meals == p->t->nb || p->t->nb == 1 || p->t->is_dead)
			return (NULL);
		say_me(p->t, p->id, "is sleeping ...");
		acc_sleep(p->t->time_to_sleep);
		if (p->t->max_meal == p->t->nb || p->t->is_dead)
			return (NULL);
		say_me(p->t, p->id, "is thinking ...");
	}
	return (NULL);
}
*/
void	*better_life(void *arg)
{
	t_philo	*p;

	p = arg;
	while (p->t->power == OFF)
		;
	p->last_meal = p->t->start;
	while (p->t->power == ON)
	{
		eat(p);
		if (compare_time(p->last_meal) >= p->t->time_to_die
			|| p->meals == p->t->max_meal)
		{
			p->t->power = OFF;
		}
		if (p->t->nb == 1 || p->t->power == OFF)
			return (NULL);
		phil_sleep(p);
		if (p->meals == p->t->max_meal || p->t->power == OFF)
			return (NULL);
		think(p);
	}
	return (NULL);
}

static void	check_life(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->nb)
	{
		pthread_mutex_lock(&t->death[i]);
		if (compare_time(t->philo[i].last_meal) >= t->time_to_die
			|| t->power == OFF)
		{
			t->power = OFF;
			say_me(t, i, "is dead");
			pthread_mutex_unlock(&t->death[i]);
			return ;
		}
		pthread_mutex_unlock(&t->death[i]);
		i++;
	}
	usleep(50);
}

static void	start_time(t_table *t)
{
	gettimeofday(&t->time, NULL);
	t->start = get_time();
	t->power = ON;
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
	if (nb_philo > 0)
		if (init(&table, nb_philo) == -1)
			return (msg_err("Malloc failed: ", "Insufficient memory!\n", 22));
	init_struct(&table, av);
	if (!table.nb || !table.time_to_die || !table.time_to_eat
		|| !table.time_to_sleep || !table.max_meal)
		ft_err(&table, "Arg: ", 2);
	// print_table(&table);
	start_time(&table);
	check_life(&table);
	while (++i < table.nb)
		pthread_join(table.philo[i].thread, NULL);
	print_table(&table);
	free_struct(&table);
	return (0);
}
