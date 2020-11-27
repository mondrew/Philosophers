/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 00:20:53 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 13:59:52 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_thread(void *philo, int *i, struct timeval *time, \
														t_time *last_eat)
{
	sem_wait(((t_data *)philo)->start_time);
	if (((t_data *)philo)->start.sec == -1 && \
			((t_data *)philo)->start.usec == -1)
	{
		gettimeofday(time, NULL);
		((t_data *)philo)->start.sec = time->tv_sec;
		((t_data *)philo)->start.usec = time->tv_usec;
	}
	last_eat->sec = ((t_data *)philo)->start.sec;
	last_eat->usec = ((t_data *)philo)->start.usec;
	sem_post(((t_data *)philo)->start_time);
	sem_wait(((t_data *)philo)->block_mutex);
	if (((t_data *)philo)->race_win == -1)
	{
		((t_data *)philo)->race_win = *i;
		((t_data *)philo)->block_at_start[ft_left(*i, \
			((t_data *)philo)->number_of_philosophers)] = 1;
		((t_data *)philo)->block_at_start[ft_right(*i, \
			((t_data *)philo)->number_of_philosophers)] = 1;
	}
	sem_post(((t_data *)philo)->block_mutex);
}

void	ft_get_thread_number(void *philo, int *i)
{
	sem_wait(((t_data *)philo)->thread_number);
	while (((t_data *)philo)->thread_num_array[*i] != 0)
		(*i)++;
	((t_data *)philo)->thread_num_array[*i] = *i + 1;
	sem_post(((t_data *)philo)->thread_number);
}

int		ft_eating(void *philo, t_time *last_eat, int *eat_count, int i)
{
	struct timeval	time;

	sem_wait(((t_data *)philo)->stop_all);
	if ((((t_data *)philo)->print_forbid != 1) && \
		(ft_print_status(philo, i, EATING) == -1))
	{
		sem_post(((t_data *)philo)->stop_all);
		ft_putstr("error: cannot allocate memory\n");
		return (-1);
	}
	sem_post(((t_data *)philo)->stop_all);
	gettimeofday(&time, NULL);
	last_eat->sec = time.tv_sec;
	last_eat->usec = time.tv_usec;
	sem_wait(((t_data *)philo)->state);
	(((t_data *)philo)->prev_eat[i]).sec = time.tv_sec;
	(((t_data *)philo)->prev_eat[i]).usec = time.tv_usec;
	sem_post(((t_data *)philo)->state);
	usleep((useconds_t)(((t_data *)philo)->time_to_eat * 1000));
	sem_post(((t_data *)philo)->forks);
	sem_post(((t_data *)philo)->forks);
	(*eat_count)++;
	((t_data *)philo)->eat_times[i] += 1;
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

void	ft_start_init(t_data *philo, int *thread_num_array, \
						int *eat_times, t_time *prev_eat)
{
	int		i;

	i = 0;
	memset(thread_num_array, 0, sizeof(int) * philo->number_of_philosophers);
	memset(eat_times, 0, sizeof(int) * philo->number_of_philosophers);
	philo->thread_num_array = thread_num_array;
	philo->eat_times = eat_times;
	philo->race_win = -1;
	while (i < philo->number_of_philosophers)
	{
		(prev_eat[i]).sec = 0;
		(prev_eat[i]).usec = 0;
		i++;
	}
	philo->prev_eat = prev_eat;
	philo->print_forbid = 0;
	philo->error = 0;
}
