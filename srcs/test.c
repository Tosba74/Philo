/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:26:18 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/04 17:26:22 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((clock_t)tv.tv_sec * 1000 + (clock_t)tv.tv_usec / 1000);
}

int	compare_time(long long time)
{
	return (get_time() - time);
}

void	acc_sleep(long long check)
{
	long long	time;

	time = get_time();
	while (get_time() - time < check)
		usleep(50);
}

void	print_philo(t_philo *p)
{
	dprintf(2, "+=============================+\n");
	dprintf(2, "| id => %2u /%2u                |\n", p->id, p->t->nb);
	dprintf(2, "| meals =>%3d  <%3d           |\n", p->meals, p->t->max_meal);
	dprintf(2, "| left => %2d || right = > %2d  |\n", p->id, p->fright);
	dprintf(2, "| Pthread %d adrress           |\n", p->id);
	dprintf(2, "| > %p            |\n", p->thread);
	dprintf(2, "| Table adrress               |\n");
	dprintf(2, "| > %p            |\n", p->t);
	dprintf(2, "+=============================+\n");
}

void	print_table(t_table *t)
{
	int	i;

	i = -1;
	dprintf(2, "+=============================+\n");
	dprintf(2, "| Nombre de philo ==> %2d      |\n", (int)t->nb);
	dprintf(2, "| Time_to_eat ==> %4d        |\n", t->time_to_die);
	dprintf(2, "| Time_to_die ==> %4d        |\n", t->time_to_eat);
	dprintf(2, "| Time_to_sleep ==> %4d      |\n", t->time_to_sleep);
	dprintf(2, "| max_meal ==> %4d      |\n", t->max_meal);
	while (++i < t->nb)
		print_philo(&t->philo[i]);
}
