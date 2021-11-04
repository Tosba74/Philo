/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:41:57 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/04 17:25:35 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_sleep(t_philo *p)
{
	say_me(p->t, p->id, "is sleeping ...");
	acc_sleep(p->t->time_to_sleep);
}

void	think(t_philo *p)
{
	say_me(p->t, p->id, "is thinking ...");
}

void	eat(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->t->fork[p->fright]);
		say_me(p->t, p->id, "take a fork!");
		if (p->t->nb == 1)
			return ;
		pthread_mutex_lock(&p->t->fork[p->fleft]);
		say_me(p->t, p->id, "take a second fork!");
	}
	else
	{
		pthread_mutex_lock(&p->t->fork[p->fleft]);
		say_me(p->t, p->id, "take a fork!");
		pthread_mutex_lock(&p->t->fork[p->fright]);
		say_me(p->t, p->id, "take a second fork!");
	}
	pthread_mutex_lock(&p->t->death[p->id]);
	p->last_meal = get_time();
	say_me(p->t, p->id, "is eating");
	pthread_mutex_unlock(&p->t->death[p->id]);
	acc_sleep(p->t->time_to_eat);
	pthread_mutex_unlock(&p->t->fork[p->fright]);
	pthread_mutex_unlock(&p->t->fork[p->fleft]);
}

void	say_me(t_table *t, int id, char *s)
{
	pthread_mutex_lock(t->speaker);
	if (t->all_eat != t->nb && !t->dead)
	{
		printf("\033[33m%i\033[0m", compare_time(t->start));
		printf("\033[32m [%d] %s\033[0m\n", id, s);
	}
	else if (s[3] == 'd')
	{
		printf("\033[33m%i\033[0m", compare_time(t->start));
		printf("\033[31m [%d] %s\033[0m\n", id, s);
	}
	pthread_mutex_unlock(t->speaker);
}
