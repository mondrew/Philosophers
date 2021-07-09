#include "philosophers.h"

int		ft_check_fin_died(t_data *philo, int *eat_count)
{
	int		i;

	i = philo->process_num;
	if (*eat_count == philo->number_of_times_each_philosopher_must_eat)
	{
		sem_wait(philo->state);
		philo->current_state[i] = FINISHED;
		sem_post(philo->state);
		return (-1);
	}
	return (0);
}

int		ft_sleep_think(t_data *philo, int i)
{
	sem_wait(philo->stop_all);
	if ((philo->print_forbid != 1) && \
				(ft_print_status(philo, i, SLEEPING) == -1))
	{
		sem_post(philo->stop_all);
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	sem_post(philo->stop_all);
	usleep((useconds_t)(philo->time_to_sleep * 1000));
	sem_wait(philo->stop_all);
	if ((philo->print_forbid != 1) && \
		(ft_print_status(philo, i, THINKING) == -1))
	{
		sem_post(philo->stop_all);
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	sem_post(philo->stop_all);
	return (0);
}

void	*ft_philo_life(t_data *philo)
{
	int				eat_count;
	t_time			last_eat;
	struct timeval	time;
	int				i;

	eat_count = 0;
	i = philo->process_num;
	ft_init_process(philo, &time, &last_eat);
	if ((pthread_create(&(philo->monitor), NULL, ft_monitor_life, \
													(void *)philo)) != 0)
		ft_monitor_error_exit(philo);
	while (1)
	{
		if (ft_take_forks(philo, i, last_eat) == -1)
			exit(1);
		if (ft_check_time(philo, time, last_eat, i) == -1)
			exit(1);
		if (ft_eating(philo, &last_eat, &eat_count, i) == -1)
			exit(1);
		if (ft_check_fin_died(philo, &eat_count) == -1)
			exit(0);
		if (ft_sleep_think(philo, i) == -1)
			exit(1);
	}
	exit(0);
}

void	ft_error_exit(pid_t *pid, t_data *philo, int i)
{
	int		n;

	n = i - 1;
	ft_putstr("error: cannot create new thread\n");
	sem_wait(philo->error_mutex);
	philo->error = 1;
	sem_post(philo->error_mutex);
	while (n >= 0)
		kill(pid[n--], SIGKILL);
	ft_destroy_semaphores(philo);
	free(philo->current_state);
	free(philo->prev_eat);
	exit(1);
}

void	ft_success_exit(pid_t *pid, t_data *philo)
{
	int		i;
	int		n;
	int		status;

	i = 0;
	n = 0;
	while (i < philo->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status == 256)
		{
			n = 0;
			while (n < philo->number_of_philosophers)
				kill(pid[n++], SIGKILL);
			break ;
		}
		i++;
	}
	ft_destroy_semaphores(philo);
	free(philo->current_state);
	free(philo->prev_eat);
}
