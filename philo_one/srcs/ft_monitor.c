#include "philosophers.h"

void	ft_init_monitor_start_time(void *philo, t_time *start)
{
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&((t_data *)philo)->start_time);
		if (((t_data *)philo)->start.sec != -1 && \
					((t_data *)philo)->start.usec != -1)
		{
			start->sec = ((t_data *)philo)->start.sec;
			start->usec = ((t_data *)philo)->start.usec;
			pthread_mutex_unlock(&((t_data *)philo)->start_time);
			break ;
		}
		pthread_mutex_unlock(&((t_data *)philo)->start_time);
	}
	while (i < ((t_data *)philo)->number_of_philosophers)
	{
		pthread_mutex_lock(&((t_data *)philo)->state);
		((t_data *)philo)->prev_eat[i].sec = start->sec;
		((t_data *)philo)->prev_eat[i].usec = start->usec;
		pthread_mutex_unlock(&((t_data *)philo)->state);
		i++;
	}
}

int		ft_scanning_threads(void *philo, struct timeval time, \
												int *finished, int i)
{
	while (i < ((t_data *)philo)->number_of_philosophers)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&((t_data *)philo)->state);
		if ((((t_data *)philo)->current_state[i] != EATING) && \
			(((t_data *)philo)->current_state[i] != FINISHED) && \
			(((time.tv_sec - ((t_data *)philo)->prev_eat[i].sec) * 1000 + \
			(time.tv_usec - ((t_data *)philo)->prev_eat[i].usec) / 1000) > \
			(((t_data *)philo)->time_to_die)))
		{
			((t_data *)philo)->current_state[i] = DIED;
			pthread_mutex_unlock(&((t_data *)philo)->state);
			pthread_mutex_lock(&((t_data *)philo)->stop_all);
			((t_data *)philo)->print_forbid = 1;
			pthread_mutex_unlock(&((t_data *)philo)->stop_all);
			ft_print_status(philo, i, DIED);
			return (1);
		}
		if (((t_data *)philo)->current_state[i] == FINISHED)
			(*finished)++;
		pthread_mutex_unlock(&((t_data *)philo)->state);
		i++;
	}
	return (0);
}

void	*ft_scan_time(void *philo, struct timeval time)
{
	int		i;
	int		finished;

	while (1)
	{
		i = 0;
		finished = 0;
		pthread_mutex_lock(&((t_data *)philo)->error_mutex);
		if (((t_data *)philo)->error == 1)
		{
			pthread_mutex_unlock(&((t_data *)philo)->error_mutex);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&((t_data *)philo)->error_mutex);
		if (ft_scanning_threads(philo, time, &finished, i) == 1)
			return (NULL);
		if (finished == ((t_data *)philo)->number_of_philosophers)
			return (NULL);
	}
	return (NULL);
}

void	*ft_monitor_life(void *philo)
{
	struct timeval	time;
	t_time			start;

	ft_init_monitor_start_time(philo, &start);
	if (ft_scan_time(philo, time) == NULL)
		return (NULL);
	return (NULL);
}

void	ft_monitor_error_exit(pthread_t monitor, t_data *philo)
{
	ft_putstr("error: cannot create new thread\n");
	pthread_join(monitor, NULL);
	ft_destroy_mutexes(philo);
	free(philo->forks);
	free(philo->current_state);
	exit(1);
}
