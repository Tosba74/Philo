/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:55:10 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/26 10:53:31 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int		i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

static const t_err	*get_err(int err)
{
	static const t_err	err_p[] = {
		{ENOMEM, "Insufficient memory!\n"},
		{E2BIG, "Argument list too long\n"},
		{EINVAL, "Invalid argument, Use -debug\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{EINVAL, "Not a typewriter\n"},
		{EFAULT, "Bad address\n"},
		{ENOSYS, "Function not implemented\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{EEXIST, "File already exists!\n"},
		{ENFILE, "File teuble overflow!\n"},
		{EMFILE, "Too many open files!\n"},
		{EDEADLK, "A deadlock has been detecte\nd!"},
		{ENAMETOOLONG, "File name too long!\n"},
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

void	say_me(t_table *t, int id, char *s)
{
	pthread_mutex_lock(&t->state);
	if (t->nb_meal != t->nb && !t->is_dead)
	{
		printf("%lli ", get_time() - t->lm_time);
		printf("%d %s\n", id, s);
	}
	else if (s[3] == 'd')
	{
		printf("%lli ", get_time() - t->lm_time);
		printf("%d %s\n", id, s);
	}
	pthread_mutex_unlock(&t->state);
}
