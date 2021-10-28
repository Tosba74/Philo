/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:57:41 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/28 18:07:17 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*better_life(void *arg)
{
	t_philo	*p;

	p = arg;
	// printf("\033[32mPHILO #%d\033[0m\n", p->id);
	// printf("\033[33mPHILO #%d\033[0m\n", p->id);
	while (!p->t->ready)
		;
	p->last_meal = p->t->lm_time;
	while (!p->t->is_dead || p->meals < p->t->max_meal)
	{
		say_me(p->t, p->id, "thinking ...");
		pthread_mutex_lock(&p->t->fork[p->fleft]);
		pthread_mutex_lock(&p->t->fork[p->frigth]);
		say_me(p->t, p->id, "take a fork!");
		say_me(p->t, p->id, "eating ...");
		p->meals++;
		p->last_meal = compare_time(p->last_meal);
		if (p->meals > p->t->nb_meal)
			p->t->nb_meal = p->meals;
		pthread_mutex_unlock(&p->t->fork[p->fleft]);
		pthread_mutex_unlock(&p->t->fork[p->frigth]);
		say_me(p->t, p->id, "sleeping ...");
		usleep(500);
	}
	p->t->is_dead = 1;
	// print_philo((t_philo *)arg);
	/*
	t_philo	*p;

	p = arg;
	dprintf(2, "\033[34mPhilo #%u \033[0m\n", p->t->nb);
	dprintf(2, "\033[32mPhilo %d think = %d\033[0m\n",
		p->id, p->state);
	p->state += 1;
	if (pthread_mutex_lock(&p->t->fork[p->id])
		& pthread_mutex_lock(&p->t->fork[(p->id + 1) % p->t->nb]))
	{
		dprintf(2, "\033]33mPhilo %d eat = %d\033[0m\n",
			p->id, p->state);
		usleep(100);
	}
	pthread_mutex_lock(&p->t->fork[p->id]);
	pthread_mutex_lock(&p->t->fork[(p->id + 1) % p->t->nb]);
	p->state += 1;
	dprintf(2, "\033]31mPhilo %d sleep = %d\033[0m\n",
		p->id, p->state);
	*/
	return (0);
}

static void	check_life(t_table *t)
{
	int i;

	i = 0;
	while (i < t->nb)
	{
		pthread_mutex_lock(&t->eating);
		if (get_time() - t->philo[i].last_meal > t->time_to_die
			&& t->max_meal != t->nb)
		{
			t->is_dead= 1;
			say_me(t, i, "is dead");
			pthread_mutex_unlock(&t->eating);
			return ;
		}
		pthread_mutex_unlock(&t->eating);
		i++;
	}
	usleep(50);
}
	// while (!t->is_dead || t->nb_meal < t->max_meal)
		// usleep(50);
	// while (i++ <= t->nb)
	// {
		// pthread_mutex_unlock(&t->fork[i]);
		// pthread_mutex_destroy(&t->fork[i]);
	// }
	// pthread_mutex_unlock(&t->philo[i].death);
	// pthread_mutex_destroy(&t->philo[i].death);
	// pthread_mutex_unlock(&t->state);
	// pthread_mutex_destroy(&t->state);
// }

static void	start_time(t_table *t)
{
	sleep(5);
	gettimeofday(&t->start, NULL);
	t->lm_time = get_time();
	t->ready++;
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
	if (init(&table, nb_philo) == -1)
		return (msg_err("Malloc failed: ", "Insufficient memory!\n", 22));
	init_struct(&table, av);
	if (!table.nb || !table.time_to_die || !table.time_to_eat
		|| !table.time_to_sleep || !table.max_meal)
		ft_err(&table, "Arg: ", 2);
	start_time(&table);
	check_life(&table);
	while (++i < table.nb)
		pthread_join(table.philo[i].thread, NULL);
	free_struct(&table);
	return (0);
}
