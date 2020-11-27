/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_destroy_semaphores.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:51:59 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 21:40:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_semaphores(t_data *philo)
{
	philo->forks = sem_open("forks", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, \
												philo->number_of_philosophers);
	sem_unlink("forks");
	philo->state = sem_open("state", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, 1);
	sem_unlink("state");
	philo->printer = sem_open("printer", O_CREAT, 0777, 1);
	sem_unlink("printer");
	philo->start_time = sem_open("start_time", O_CREAT, 0777, 1);
	sem_unlink("start_time");
	philo->stop_all = sem_open("stop_all", O_CREAT, 0777, 1);
	sem_unlink("stop_all");
	philo->error_mutex = sem_open("error_mutex", O_CREAT, 0777, 1);
	sem_unlink("error_mutex");
	philo->start_eat = sem_open("start_eat", O_CREAT, 0777, 1);
	sem_unlink("start_eat");
}

void	ft_destroy_semaphores(t_data *philo)
{
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
}
