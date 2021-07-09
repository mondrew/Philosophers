#include "philosophers.h"

void	ft_init_semaphores(t_data *philo)
{
	philo->forks = sem_open("forks", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, \
												philo->number_of_philosophers);
	sem_unlink("forks");
	philo->state = sem_open("state", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, 1);
	sem_unlink("state");
	philo->thread_number = sem_open("thread_number", O_CREAT, \
											S_IRWXU | S_IRWXG | S_IRWXO, 1);
	sem_unlink("thread_number");
	philo->printer = sem_open("printer", O_CREAT, 0777, 1);
	sem_unlink("printer");
	philo->start_time = sem_open("start_time", O_CREAT, 0777, 1);
	sem_unlink("start_time");
	philo->block_mutex = sem_open("block_mutex", O_CREAT, 0777, 1);
	sem_unlink("block_mutex");
	philo->stop_all = sem_open("stop_all", O_CREAT, 0777, 1);
	sem_unlink("stop_all");
	philo->error_mutex = sem_open("error_mutex", O_CREAT, 0777, 1);
	sem_unlink("error_mutex");
	philo->start_eat = sem_open("start_eat", O_CREAT, 0777, 1);
	sem_unlink("start_eat");
	philo->check_eat_times = sem_open("check_eat_times", O_CREAT, 0777, 1);
	sem_unlink("check_eat_times");
}

void	ft_destroy_semaphores(t_data *philo)
{
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
}
