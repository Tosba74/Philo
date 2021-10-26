#include "philo.h"

void	*better_life(void *arg)
{
	printf("\n\033[33mPHILO #%d\033[0m\n", ((t_philo *)arg)->id);
	while (!((t_philo *)arg)->t->ready)
		return (0);
	((t_philo *)arg)->last_meal = ((t_philo *)arg)->t->lm_time;
	printf("\n\033[32mPHILO #%d\033[0m\n", ((t_philo *)arg)->id);
	say_me(((t_philo *)arg)->t, ((t_philo *)arg)->id, "JAI LA DALLE\n");
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
	return(0);
}

int	main(int ac, char **av)
{
	int			nb_philo;
	t_table		table;

	if (ac > 6)
		return (msg_err("Arg: ", "Argument list too long\n", 7));
	if (ac < 5)
		return (msg_err("Arg: ", "Argument list too short\n", 7));
	nb_philo = ft_atoi(av[1]);
	table = (t_table){};
	if (nb_philo < 2 || nb_philo > 7)
		return (msg_err("First arg: ", "Invalid argument\n", 22));
	if (init(&table, nb_philo) == -1)
		return (msg_err("Malloc failed: ", "Insufficient memory!\n", 22));
	init_struct(&table, av);
	sleep(5);
	printf("\n\033[31mREADY\033[0m\n");
	
	// print_table(&table);
	// printf("%d != %d\n", nb_philo, table.nb);
	// dprintf(2, "nan, je suis la !!\n");
	// print_table(&table);
	free_struct(&table);
	return (0);
}
