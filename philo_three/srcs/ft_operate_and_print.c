/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operate_and_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:19:23 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 21:54:52 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_all(t_data *philo, char *milliseconds, char *thread_number, \
																	int status)
{
	sem_wait(philo->printer);
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
	sem_post(philo->printer);
	free(milliseconds);
	free(thread_number);
}

int		ft_print_status(t_data *philo, int i, int status)
{
	struct timeval	time;
	char			*milliseconds;
	char			*thread_number;
	int				timestamp;

	gettimeofday(&time, NULL);
	sem_wait(philo->start_time);
	timestamp = (time.tv_sec - philo->start.sec) * 1000000 + \
		(time.tv_usec - philo->start.usec);
	sem_post(philo->start_time);
	if (!(milliseconds = ft_itoa(timestamp / 1000)))
		return (-1);
	if (!(thread_number = ft_itoa(i + 1)))
	{
		free(milliseconds);
		return (-1);
	}
	sem_wait(philo->state);
	(philo->current_state)[i] = status;
	sem_post(philo->state);
	ft_print_all(philo, milliseconds, thread_number, status);
	return (0);
}

int		ft_take_left_right(t_data *philo, int i)
{
	sem_wait(philo->forks);
	sem_wait(philo->stop_all);
	if ((philo->print_forbid != 1) && (ft_print_status(philo, i, FORK) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		sem_post(philo->forks);
		sem_post(philo->stop_all);
		return (-1);
	}
	sem_post(philo->stop_all);
	sem_wait(philo->forks);
	sem_wait(philo->stop_all);
	if ((philo->print_forbid != 1) && (ft_print_status(philo, i, FORK) == -1))
	{
		ft_putstr("error: cannot allocate memory\n");
		sem_post(philo->forks);
		sem_post(philo->forks);
		sem_post(philo->stop_all);
		return (-1);
	}
	sem_post(philo->stop_all);
	return (0);
}

int		ft_take_forks(t_data *philo, int i, t_time last_eat)
{
	int		ret;

	if (ft_mute_if_greedy(philo, last_eat))
		usleep((useconds_t)(philo->time_to_eat * 1000 / 100));
	sem_wait(philo->start_eat);
	ret = ft_take_left_right(philo, i);
	sem_post(philo->start_eat);
	return (ret);
}

int		ft_check_time(t_data *philo, struct timeval time, t_time last_eat, \
																		int i)
{
	gettimeofday(&time, NULL);
	if (((time.tv_sec - last_eat.sec) * 1000 + \
		(time.tv_usec - last_eat.usec) / 1000) > philo->time_to_die)
	{
		sem_wait(philo->stop_all);
		if ((philo->print_forbid != 1) && \
								(ft_print_status(philo, i, FORK) == -1))
			sem_post(philo->stop_all);
		sem_post(philo->stop_all);
		sem_post(philo->forks);
		sem_post(philo->forks);
		return (-1);
	}
	return (0);
}
