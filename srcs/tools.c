/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:13:03 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/26 10:39:00 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * neg);
}

void	free_struct(t_table *table)
{
	int	i;

	i = -1;
	print_table(table);
	while (++i < table->nb)
	{
		pthread_mutex_unlock(&table->philo[i].death);
		pthread_mutex_unlock(&table->fork[i]);
		pthread_mutex_destroy(&table->philo[i].death);
		pthread_mutex_destroy(&table->fork[i]);
	}
	if (table->fork)
		free(table->fork);
	if (table->philo)
		free(table->philo);
}
