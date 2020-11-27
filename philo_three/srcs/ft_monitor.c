/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:31:35 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 22:04:25 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_monitor_start_time(t_data *philo, t_time *local_start)
{
	int		i;

	i = 0;
	while (1)
	{
		sem_wait(philo->start_time);
		if (philo->start.sec != -1 && philo->start.usec != -1)
		{
			local_start->sec = philo->start.sec;
			local_start->usec = philo->start.usec;
			sem_post(philo->start_time);
			break ;
		}
		sem_post(philo->start_time);
	}
	while (i < philo->number_of_philosophers)
	{
		sem_wait(philo->state);
		(philo->prev_eat[i]).sec = local_start->sec;
		(philo->prev_eat[i]).usec = local_start->usec;
		sem_post(philo->state);
		i++;
	}
}

int		ft_scanning_threads(t_data *philo, struct timeval time)
{
	int		i;

	i = philo->process_num;
	gettimeofday(&time, NULL);
	sem_wait(philo->state);
	if (philo->current_state[i] == FINISHED)
	{
		sem_post(philo->state);
		exit(0);
	}
	if ((philo->current_state[i] != EATING) && (philo->current_state[i] != \
		FINISHED) && (((time.tv_sec - philo->prev_eat[i].sec) * 1000 + \
		(time.tv_usec - philo->prev_eat[i].usec) / 1000) > philo->time_to_die))
	{
		philo->current_state[i] = DIED;
		sem_post(philo->state);
		sem_wait(philo->stop_all);
		philo->print_forbid = 1;
		sem_post(philo->stop_all);
		ft_print_status(philo, i, DIED);
		sem_wait(philo->printer);
		return (1);
	}
	sem_post(philo->state);
	return (0);
}

void	*ft_scan_time(t_data *philo, struct timeval time)
{
	while (1)
	{
		sem_wait(philo->error_mutex);
		if (philo->error == 1)
		{
			sem_post(philo->error_mutex);
			return (NULL);
		}
		else
			sem_post(philo->error_mutex);
		if (ft_scanning_threads(philo, time) == 1)
			return (NULL);
	}
	return (NULL);
}

void	*ft_monitor_life(void *philo)
{
	struct timeval	time;
	t_time			local_start;

	ft_init_monitor_start_time((t_data *)philo, &local_start);
	if (ft_scan_time((t_data *)philo, time) == NULL)
		exit(1);
	exit(0);
}

void	ft_monitor_error_exit(t_data *philo)
{
	ft_putstr("error: cannot create new thread\n");
	if (sem_close(philo->forks) == -1)
		ft_putstr("error: cannot close fork semaphore\n");
	if (sem_close(philo->state) == -1)
		ft_putstr("error: cannot close state semaphore\n");
	if (sem_close(philo->printer) == -1)
		ft_putstr("error: cannot close printer semaphore\n");
	if (sem_close(philo->start_time) == -1)
		ft_putstr("error: cannot close start_time semaphore\n");
	if (sem_close(philo->stop_all) == -1)
		ft_putstr("error: cannot close stop_all semaphore\n");
	if (sem_close(philo->error_mutex) == -1)
		ft_putstr("error: cannot close error_mutex semaphore\n");
	if (sem_close(philo->start_eat) == -1)
		ft_putstr("error: cannot close start_eat semaphore\n");
	free(philo->current_state);
	free(philo->prev_eat);
	exit(1);
}
