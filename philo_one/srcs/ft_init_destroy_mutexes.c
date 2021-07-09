#include "philosophers.h"

void	ft_init_mutexes(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
		pthread_mutex_init(&philo->forks[i++], NULL);
	pthread_mutex_init(&philo->state, NULL);
	pthread_mutex_init(&philo->thread_number, NULL);
	pthread_mutex_init(&philo->printer, NULL);
	pthread_mutex_init(&philo->start_time, NULL);
	pthread_mutex_init(&philo->block_mutex, NULL);
	pthread_mutex_init(&philo->stop_all, NULL);
	pthread_mutex_init(&philo->error_mutex, NULL);
}

void	ft_destroy_mutexes(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&philo->forks[i]) != 0)
			ft_putstr("error: cannot destroy fork mutex\n");
		i++;
	}
	if (pthread_mutex_destroy(&philo->state) != 0)
		ft_putstr("error: cannot destroy state mutex\n");
	if (pthread_mutex_destroy(&philo->thread_number) != 0)
		ft_putstr("error: cannot destroy thread_number mutex\n");
	if (pthread_mutex_destroy(&philo->printer) != 0)
		ft_putstr("error: cannot destroy printer mutex\n");
	if (pthread_mutex_destroy(&philo->start_time) != 0)
		ft_putstr("error: cannot destroy start_time mutex\n");
	if (pthread_mutex_destroy(&philo->block_mutex) != 0)
		ft_putstr("error: cannot destroy block_mutex mutex\n");
	if (pthread_mutex_destroy(&philo->stop_all) != 0)
		ft_putstr("error: cannot destroy stop_all mutex\n");
	if (pthread_mutex_destroy(&philo->error_mutex) != 0)
		ft_putstr("error: cannot destroy error_mutex mutex\n");
}
