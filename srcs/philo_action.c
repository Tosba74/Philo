/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:41:57 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/27 10:12:20 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_sleep(t_philo *philo)
{
	(void)philo;
	dprintf(STDERR_FILENO, "Philo sleep\n");
}

void	p_think(t_philo *philo)
{
	(void)philo;
	dprintf(STDERR_FILENO, "Philo think\n");
}

void	p_eat(t_philo *philo)
{
	(void)philo;
	dprintf(STDERR_FILENO, "Philo eat\n");
}
