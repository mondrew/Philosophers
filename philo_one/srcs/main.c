#include "philosophers.h"

void	ft_philosophers_one(t_data *philo, int i)
{
	int			status;
	int			thread_num_array[philo->number_of_philosophers];
	int			block_at_start[philo->number_of_philosophers];
	pthread_t	pthread[philo->number_of_philosophers];
	t_time		prev_eat[philo->number_of_philosophers];

	i = 0;
	ft_start_init(philo, thread_num_array, block_at_start, prev_eat);
	ft_init_mutexes(philo);
	if ((status = pthread_create(&(philo->monitor), NULL, ft_monitor_life, \
													(void *)philo)) != 0)
		ft_monitor_error_exit(philo->monitor, philo);
	while (i < philo->number_of_philosophers)
	{
		if ((status = pthread_create(&pthread[i], NULL, ft_philo_life, \
														(void *)philo)) != 0)
			ft_error_exit(pthread, philo->monitor, philo, i);
		i++;
	}
	ft_success_exit(pthread, philo->monitor, philo);
}

void	ft_fill_state_time(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->current_state[i] = THINKING;
		i++;
	}
	philo->start.sec = -1;
	philo->start.usec = -1;
}

int		ft_fill_struct(t_data *philo, char **argv)
{
	if (!(philo->number_of_philosophers = ft_atoi(argv[1])) || \
		!(philo->time_to_die = ft_atoi(argv[2])) || \
		!(philo->time_to_eat = ft_atoi(argv[3])) || \
		!(philo->time_to_sleep = ft_atoi(argv[4])))
		return (-1);
	if (argv[5] == NULL)
		philo->number_of_times_each_philosopher_must_eat = -1;
	else if (!(philo->number_of_times_each_philosopher_must_eat = \
														ft_atoi(argv[5])))
		return (-1);
	if (!(philo->current_state = malloc(sizeof(int) * \
											philo->number_of_philosophers)))
		return (-1);
	if (!(philo->forks = malloc(sizeof(pthread_mutex_t) * \
											philo->number_of_philosophers)))
	{
		free(philo->current_state);
		return (-1);
	}
	ft_fill_state_time(philo);
	return (0);
}

int		ft_check_arguments(char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	t_data	philo;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		ft_putstr("error: wrong number of arguments\n");
		return (1);
	}
	if (ft_check_arguments(argv) == -1)
	{
		ft_putstr("error: wrong arguments\n");
		return (1);
	}
	if (ft_fill_struct(&philo, argv) == -1)
	{
		if (!philo.current_state)
			ft_putstr("error: cannot allocate memory\n");
		else
			ft_putstr("error: wrong arguments\n");
		return (1);
	}
	ft_philosophers_one(&philo, i);
	return (0);
}
