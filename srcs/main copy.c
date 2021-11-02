#include "philo.h"

#define NB_PHILO 5

void	*better_life(void *arg)
{
	t_philo	*philo;

	philo = arg;
	dprintf(2, "\033[34mPhilo #%d \033[0m\n", philo->nb);
	dprintf(2, "\033[32mPhilo %d is thinking = %d\033[0m\n",
		philo->id, philo->speaker);
	philo->speaker += 1;
	pthread_mutex_lock(&philo->fork);
	dprintf(2, "\033]33mPhilo %d is eating = %d\033[0m\n",
		philo->id, philo->speaker);
	philo->speaker == SLEEPING;
	dprintf(2, "\033]31mPhilo %d is sleeping = %d\033[0m\n",
		philo->id, philo->speaker);
	return 0;
}

t_philo	**init_philo_thread(void)
{
	int			i;
	t_philo		**philo;

	i = -1;
	philo = (t_philo **)malloc(sizeof(t_philo *) * NB_PHILO);
	if (!(philo))
		ft_err("Malloc all struct", 0);
	while (++i < NB_PHILO)
	{
		dprintf(2, "\033[36mInit_Philo #%d \033[0m\n", i);
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!(philo[i]))
			ft_err("Malloc philo's struct", 0);
		philo[i]->nb = NB_PHILO;
		philo[i]->id = i;
		philo[i]->time_to_die = 63;
		philo[i]->time_to_eat = 63;
		philo[i]->max_meal = 63;
		philo[i]->time_to_sleep = 63;
		philo[i]->speaker = THINKING;
		pthread_create(&philo[i]->thread, NULL, &better_life, philo[i]);
		if (!(philo[i]->fork = malloc(sizeof(pthread_mutex_t))))
			ft_err("Malloc mutex", 0);
		pthread_mutex_init(&philo[i]->fork, NULL);
	}
	return (philo);
}

void	philo(char **av)
{
	(void)av;
}

// int main(int ac, char **av)
int main(void)
{
	t_philo	**p;

	p = init_philo_thread();
	return (0);
}
