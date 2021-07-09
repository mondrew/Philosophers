#include "philosophers.h"

void	ft_print_all(void *philo, char *milliseconds, char *thread_number, \
																	int status)
{
	pthread_mutex_lock(&((t_data *)philo)->printer);
	ft_putstr(milliseconds);
	ft_putstr(" ");
	ft_putstr(thread_number);
	if (status == FORK)
		ft_putstr(" has taken a fork\n");
	else if (status == EATING)
		ft_putstr(" is eating\n");
	else if (status == SLEEPING)
		ft_putstr(" is sleeping\n");
	else if (status == THINKING)
		ft_putstr(" is thinking\n");
	else if (status == DIED)
		ft_putstr(" died\n");
	pthread_mutex_unlock(&((t_data *)philo)->printer);
	free(milliseconds);
	free(thread_number);
}

int		ft_print_status(void *philo, int i, int status)
{
	struct timeval	time;
	char			*milliseconds;
	char			*thread_number;
	int				timestamp;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&((t_data *)philo)->start_time);
	timestamp = (time.tv_sec - ((t_data *)philo)->start.sec) * 1000000 + \
		(time.tv_usec - ((t_data *)philo)->start.usec);
	pthread_mutex_unlock(&((t_data *)philo)->start_time);
	if (!(milliseconds = ft_itoa(timestamp / 1000)))
		return (-1);
	if (!(thread_number = ft_itoa(i + 1)))
	{
		free(milliseconds);
		return (-1);
	}
	pthread_mutex_lock(&((t_data *)philo)->state);
	((t_data *)philo)->current_state[i] = status;
	pthread_mutex_unlock(&((t_data *)philo)->state);
	ft_print_all(philo, milliseconds, thread_number, status);
	return (0);
}

int		ft_take_left_right(void *philo, int i)
{
	pthread_mutex_lock(&((t_data *)philo)->forks[i]);
	pthread_mutex_lock(&((t_data *)philo)->stop_all);
	if ((((t_data *)philo)->print_forbid != 1) && \
		(ft_print_status(philo, i, FORK) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		pthread_mutex_unlock(&((t_data *)philo)->forks[i]);
		return (-1);
	}
	pthread_mutex_unlock(&((t_data *)philo)->stop_all);
	pthread_mutex_lock(&((t_data *)philo)->forks[ft_right(i, \
						((t_data *)philo)->number_of_philosophers)]);
	pthread_mutex_lock(&((t_data *)philo)->stop_all);
	if ((((t_data *)philo)->print_forbid != 1) && \
		(ft_print_status(philo, i, FORK) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		pthread_mutex_unlock(&((t_data *)philo)->forks[i]);
		pthread_mutex_unlock(&((t_data *)philo)->forks[ft_right(i, \
							((t_data *)philo)->number_of_philosophers)]);
		return (-1);
	}
	pthread_mutex_unlock(&((t_data *)philo)->stop_all);
	return (0);
}

int		ft_take_forks(void *philo, int i)
{
	int		ret;

	pthread_mutex_lock(&((t_data *)philo)->block_mutex);
	if (((t_data *)philo)->block_at_start[i] == 1)
	{
		((t_data *)philo)->block_at_start[i] = 0;
		pthread_mutex_unlock(&((t_data *)philo)->block_mutex);
		usleep((useconds_t)(((t_data *)philo)->time_to_eat * 1000 / 10));
	}
	else
		pthread_mutex_unlock(&((t_data *)philo)->block_mutex);
	ret = ft_take_left_right(philo, i);
	return (ret);
}

int		ft_check_time(void *philo, struct timeval time, t_time last_eat, int i)
{
	gettimeofday(&time, NULL);
	if (((time.tv_sec - last_eat.sec) * 1000 + \
		(time.tv_usec - last_eat.usec) / 1000) > \
			(((t_data *)philo)->time_to_die))
	{
		pthread_mutex_lock(&((t_data *)philo)->state);
		((t_data *)philo)->current_state[i] = DIED;
		pthread_mutex_unlock(&((t_data *)philo)->state);
		pthread_mutex_unlock(&((t_data *)philo)->forks[i]);
		pthread_mutex_unlock(&((t_data *)philo)->forks[ft_right(i, \
							((t_data *)philo)->number_of_philosophers)]);
		return (-1);
	}
	return (0);
}
