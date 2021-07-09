#include "philosophers.h"

void	ft_init_monitor_start_time(void *philo, t_time *start)
{
	int		i;

	i = 0;
	while (1)
	{
		sem_wait(((t_data *)philo)->start_time);
		if (((t_data *)philo)->start.sec != -1 && \
					((t_data *)philo)->start.usec != -1)
		{
			start->sec = ((t_data *)philo)->start.sec;
			start->usec = ((t_data *)philo)->start.usec;
			sem_post(((t_data *)philo)->start_time);
			break ;
		}
		sem_post(((t_data *)philo)->start_time);
	}
	while (i < ((t_data *)philo)->number_of_philosophers)
	{
		sem_wait(((t_data *)philo)->state);
		((t_data *)philo)->prev_eat[i].sec = start->sec;
		((t_data *)philo)->prev_eat[i].usec = start->usec;
		sem_post(((t_data *)philo)->state);
		i++;
	}
}

int		ft_scanning_threads(void *philo, struct timeval time, \
												int *finished, int i)
{
	while (i < ((t_data *)philo)->number_of_philosophers)
	{
		gettimeofday(&time, NULL);
		sem_wait(((t_data *)philo)->state);
		if ((((t_data *)philo)->current_state[i] != EATING) && \
			(((t_data *)philo)->current_state[i] != FINISHED) && \
			(((time.tv_sec - ((t_data *)philo)->prev_eat[i].sec) * 1000 + \
			(time.tv_usec - ((t_data *)philo)->prev_eat[i].usec) / 1000) > \
			(((t_data *)philo)->time_to_die)))
		{
			((t_data *)philo)->current_state[i] = DIED;
			sem_post(((t_data *)philo)->state);
			sem_wait(((t_data *)philo)->stop_all);
			((t_data *)philo)->print_forbid = 1;
			sem_post(((t_data *)philo)->stop_all);
			ft_print_status(philo, i, DIED);
			return (1);
		}
		if (((t_data *)philo)->current_state[i] == FINISHED)
			(*finished)++;
		sem_post(((t_data *)philo)->state);
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
		sem_wait(((t_data *)philo)->error_mutex);
		if (((t_data *)philo)->error == 1)
		{
			sem_post(((t_data *)philo)->error_mutex);
			return (NULL);
		}
		else
			sem_post(((t_data *)philo)->error_mutex);
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

void	ft_monitor_error_exit(t_data *philo)
{
	ft_putstr("error: cannot create new thread\n");
	if (sem_close(philo->forks) == -1)
		ft_putstr("error: cannot close fork semaphore\n");
	if (sem_close(philo->state) == -1)
		ft_putstr("error: cannot close state semaphore\n");
	if (sem_close(philo->thread_number) == -1)
		ft_putstr("error: cannot close thread_number semaphore\n");
	if (sem_close(philo->printer) == -1)
		ft_putstr("error: cannot close printer semaphore\n");
	if (sem_close(philo->start_time) == -1)
		ft_putstr("error: cannot close start_time semaphore\n");
	if (sem_close(philo->block_mutex) == -1)
		ft_putstr("error: cannot close block_mutex semaphore\n");
	if (sem_close(philo->stop_all) == -1)
		ft_putstr("error: cannot close stop_all semaphore\n");
	if (sem_close(philo->error_mutex) == -1)
		ft_putstr("error: cannot close error_mutex semaphore\n");
	if (sem_close(philo->start_eat) == -1)
		ft_putstr("error: cannot close start_eat semaphore\n");
	if (sem_close(philo->check_eat_times) == -1)
		ft_putstr("error: cannot close check_eat_times semaphore\n");
	free(philo->current_state);
	exit(1);
}
