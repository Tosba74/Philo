/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:54:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/26 18:05:31 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((clock_t)tv.tv_sec * 1000 + (clock_t)tv.tv_usec / 1000);
}

int	compare_time(long time)
{
	return (time < get_time_ms());
}

void	acc_sleep(long check)
{
	long	time;

	time = get_time_ms();
	while (get_time_ms() - time < check)
		usleep(50);
}

void	print_philo(t_philo *p)
{
	dprintf(2, "+=============================+\n");
	dprintf(2, "| id => %2u || state = > %2d    |\n", p->id, p->state);
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
	dprintf(2, "| Time_to_think ==> %4d      |\n", t->time_to_think);
	dprintf(2, "| Time: %2d:%2d                 |\n", compare_time(get_time_ms()), 0);
	while (++i < t->nb)
		print_philo(&t->philo[i]);
}
