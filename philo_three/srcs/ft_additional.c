/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 00:20:53 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 21:56:48 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_process(t_data *philo, struct timeval *time, \
														t_time *last_eat)
{
	sem_wait(philo->start_time);
	if (philo->start.sec == -1 && philo->start.usec == -1)
	{
		gettimeofday(time, NULL);
		philo->start.sec = time->tv_sec;
		philo->start.usec = time->tv_usec;
	}
	last_eat->sec = philo->start.sec;
	last_eat->usec = philo->start.usec;
	sem_post(philo->start_time);
}

int		ft_eating(t_data *philo, t_time *last_eat, int *eat_count, int i)
{
	struct timeval	time;

	sem_wait(philo->stop_all);
	if ((philo->print_forbid != 1) && (ft_print_status(philo, i, EATING) == -1))
	{
		sem_post(philo->stop_all);
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	sem_post(philo->stop_all);
	gettimeofday(&time, NULL);
	last_eat->sec = time.tv_sec;
	last_eat->usec = time.tv_usec;
	sem_wait(philo->state);
	(philo->prev_eat[i]).sec = time.tv_sec;
	(philo->prev_eat[i]).usec = time.tv_usec;
	sem_post(philo->state);
	usleep((useconds_t)(philo->time_to_eat * 1000));
	sem_post(philo->forks);
	sem_post(philo->forks);
	(*eat_count)++;
	return (0);
}

int		ft_check_if_died(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo->current_state[i] == DIED)
			return (1);
		i++;
	}
	return (0);
}

void	ft_start_init(t_data *philo)
{
	int		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		(philo->prev_eat[i]).sec = 0;
		(philo->prev_eat[i]).usec = 0;
		i++;
	}
}
