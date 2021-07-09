#include "philosophers.h"

int		ft_check_fin_died(void *philo, int *eat_count, int i)
{
	if (*eat_count == \
			((t_data *)philo)->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&((t_data *)philo)->state);
		((t_data *)philo)->current_state[i] = FINISHED;
		pthread_mutex_unlock(&((t_data *)philo)->state);
		return (-1);
	}
	pthread_mutex_lock(&((t_data *)philo)->state);
	if (ft_check_if_died((t_data *)philo))
	{
		pthread_mutex_unlock(&((t_data *)philo)->state);
		return (-1);
	}
	pthread_mutex_unlock(&((t_data *)philo)->state);
	return (0);
}

int		ft_sleep_think(void *philo, int i)
{
	pthread_mutex_lock(&((t_data *)philo)->stop_all);
	if ((((t_data *)philo)->print_forbid != 1) && \
		(ft_print_status(philo, i, SLEEPING) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	pthread_mutex_unlock(&((t_data *)philo)->stop_all);
	usleep((useconds_t)(((t_data *)philo)->time_to_sleep * 1000));
	pthread_mutex_lock(&((t_data *)philo)->stop_all);
	if ((((t_data *)philo)->print_forbid != 1) && \
		(ft_print_status(philo, i, THINKING) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	pthread_mutex_unlock(&((t_data *)philo)->stop_all);
	return (0);
}

void	*ft_philo_life(void *philo)
{
	int				eat_count;
	t_time			last_eat;
	struct timeval	time;
	int				i;

	i = 0;
	eat_count = 0;
	ft_get_thread_number(philo, &i);
	ft_init_thread(philo, &i, &time, &last_eat);
	while (1)
	{
		if (ft_take_forks(philo, i) == -1)
			return (NULL);
		if (ft_check_time(philo, time, last_eat, i) == -1)
			return (NULL);
		if (ft_eating(philo, &last_eat, &eat_count, i) == -1)
			return (NULL);
		if (ft_check_fin_died(philo, &eat_count, i) == -1)
			return (NULL);
		if (ft_sleep_think(philo, i) == -1)
			return (NULL);
	}
	return (NULL);
}

void	ft_error_exit(pthread_t *pthread, pthread_t monitor, \
													t_data *philo, int i)
{
	int		n;

	n = i - 1;
	ft_putstr("error: cannot create new thread\n");
	pthread_mutex_lock(&(philo->error_mutex));
	philo->error = 1;
	pthread_mutex_unlock(&(philo->error_mutex));
	pthread_detach(monitor);
	while (n >= 0)
		pthread_detach(pthread[n--]);
	ft_destroy_mutexes(philo);
	free(philo->forks);
	free(philo->current_state);
	exit(1);
}

void	ft_success_exit(pthread_t *pthread, pthread_t monitor, t_data *philo)
{
	int		i;

	i = 0;
	pthread_join(monitor, NULL);
	while (i < philo->number_of_philosophers)
		pthread_join(pthread[i++], NULL);
	ft_destroy_mutexes(philo);
	free(philo->forks);
	free(philo->current_state);
}
