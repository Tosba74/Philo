/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:41:57 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/02 15:41:59 by bmangin          ###   ########lyon.fr   */
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
		pthread_mutex_lock(&p->t->fork[p->fleft]);
		say_me(p->t, p->id, "take a fork!");
		pthread_mutex_lock(&p->t->fork[p->s_fork]);
		say_me(p->t, p->id, "take a second fork!");
	}
	else
	{
		usleep(5);
		pthread_mutex_lock(&p->t->fork[p->s_fork]);
		say_me(p->t, p->id, "take a fork!");
		if (p->t->nb == 1)
		{
			pthread_mutex_unlock(&p->t->death[p->id]);
			return ;
		}
		pthread_mutex_lock(&p->t->fork[p->fleft]);
		say_me(p->t, p->id, "take a second fork!");
	}
	pthread_mutex_lock(&p->t->death[p->id]);
	p->last_meal = get_time();
	say_me(p->t, p->id, "is eating");
	acc_sleep(p->t->time_to_eat);
	pthread_mutex_unlock(&p->t->death[p->id]);
	pthread_mutex_unlock(&p->t->fork[p->s_fork]);
	pthread_mutex_unlock(&p->t->fork[p->fleft]);
	p->meals++;
}

/*
void	eat(t_philo *p)
{
	int	fork1;
	int	fork2;

	fork1 = p->fleft;
	fork2 = p->s_fork;
	if (fork1 > fork2)
		ft_swap(&fork1, &fork2);
	if (p->t->nb == 1)
		return ;
	pthread_mutex_lock(&p->t->fork[fork1]);
	say_me(p->t, p->id, "take a fork!");
	pthread_mutex_lock(&p->t->fork[fork2]);
	say_me(p->t, p->id, "take a second fork!");
	pthread_mutex_lock(&p->t->death[p->id]);
	say_me(p->t, p->id, "is eating");
	p->last_meal = get_time();
	acc_sleep(p->t->time_to_eat);
	pthread_mutex_unlock(&p->t->death[p->id]);
	pthread_mutex_unlock(&p->t->fork[fork2]);
	pthread_mutex_unlock(&p->t->fork[fork1]);
	p->meals++;
}
*/

void	say_me(t_table *t, int id, char *s)
{
	pthread_mutex_lock(t->speaker);
	if (t->philo[id].meals != t->max_meal && t->power == ON)
	{
		printf("\033[32m%lli\033[0m ", (long long)compare_time(t->start));
		printf("\033[33m[%d] %s\033[0m\n", id, s);
	}
	else if (s[3] == 'd')
	{
		printf("\033[32m%lli\033[0m ", (long long)compare_time(t->start));
		printf("[%d] %s\n", id, s);
	}
	pthread_mutex_unlock(t->speaker);
}
