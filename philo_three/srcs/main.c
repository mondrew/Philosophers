/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:29:28 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 22:25:15 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philosophers_three(t_data *philo)
{
	pid_t	pid[philo->number_of_philosophers];
	int		i;

	i = 0;
	ft_start_init(philo);
	ft_init_semaphores(philo);
	while (i < philo->number_of_philosophers)
	{
		philo->process_num = i;
		if ((pid[i] = fork()) == -1)
			ft_error_exit(pid, philo, i);
		if (pid[i] == 0)
			ft_philo_life(philo);
		i++;
	}
	ft_success_exit(pid, philo);
}

void	ft_fill_state_time(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		(philo->current_state)[i] = THINKING;
		i++;
	}
	(philo->start).sec = -1;
	(philo->start).usec = -1;
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
	if (!(philo->prev_eat = malloc(sizeof(t_time) * \
									philo->number_of_philosophers)))
	{
		free(philo->current_state);
		return (-1);
	}
	philo->print_forbid = 0;
	philo->error = 0;
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
	t_data	philo;

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
		if (!philo.current_state || !philo.prev_eat)
			ft_putstr("error: cannot allocate memory\n");
		else
			ft_putstr("error: wrong arguments\n");
		return (1);
	}
	ft_philosophers_three(&philo);
	return (0);
}
