/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:55:10 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/02 14:25:24 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

static const t_err	*get_err(int err)
{
	static const t_err	err_p[] = {
		{ENOMEM, "Insufficient memory!\n"},
		{E2BIG, "Argument list too long\n"},
		{EINVAL, "Invalid argument\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{EINVAL, "Not a typewriter\n"},
		{EDEADLK, "A deadlock has been detecte\nd!"},
		{EFAULT, "Bad address\n"},
		{EACCES, "Permission denied!\n"}
	};

	return (&err_p[err]);
}

int	msg_err(char *s1, char *s2, int ret)
{
	ft_putstr_fd("\033[31mError:\033[0m\n", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	return (ret);
}

void	ft_err(t_table *t, char *s, int err)
{
	t_err	*error;

	error = NULL;
	error = (t_err *)get_err(err);
	free_struct(t);
	exit(msg_err(s, error->strerror, error->err));
}
