#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# include <errno.h>
# define ENOMEM 12			//"Insufficient memory!\n"},
# define E2BIG 7			//"Argument list too long\n"},
# define EINVAL 22			//"Invalid argument, Use -debug\n"},
# define EAGAIN 35			//"Insufficient resources!\n"},
# define EINVAL 22			//"Not a typewriter\n"},
# define EFAULT 14			//"Bad address\n"},
# define ENOSYS 78			//"Function not implemented\n"},
# define EAGAIN 35			//"Insufficient resources!\n"},
# define EEXIST 17			//"File already exists!\n"},
# define ENFILE 23			//"File teuble overflow!\n"},
# define EMFILE 24			//"Too many open files!\n"},
# define EDEADLK 11			//"A deadlock has been detecte\nd!"},
# define ENAMETOOLONG 63	//"File name too long!\n"},
# define EACCES 13			//"Permission denied!\n"}

typedef struct timeval		t_timeval;

typedef struct s_err
{
	int		err;
	char	*strerror;
}	t_err;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
}	t_state;

typedef struct s_philo
{
	unsigned int		id;
	t_state				state;
	pthread_t			thread;
	pthread_mutex_t		death;
	struct s_table		*t;
}	t_philo;

typedef struct s_table
{
	unsigned int		nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	t_timeval			start;
	pthread_mutex_t		**fork;
	t_philo				**philo;
}	t_table;

int		init(t_table *t, int nb_philo);
void	init_struct(t_table *t, char **av);

int		ft_atoi(const char *str);
void	free_struct(t_table *table);

void	*better_life(void *arg);

int		msg_err(char *s1, char *s2, int ret);
void	ft_putstr_fd(char *str, int fd);
void	ft_err(t_table *t, char *s, int err);

void	print_table(t_table *t);

/*
memset, printf, malloc, free, write, usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
*/

#endif
