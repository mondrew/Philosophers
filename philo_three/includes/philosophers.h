/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:32:23 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 22:05:24 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DIED 3
# define FINISHED 4
# define FORK 5

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>

typedef struct		s_time
{
	int				sec;
	int				usec;
}					t_time;

typedef struct		s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	pthread_t		monitor;
	sem_t			*forks;
	sem_t			*state;
	sem_t			*printer;
	sem_t			*start_time;
	sem_t			*stop_all;
	sem_t			*error_mutex;

	sem_t			*start_eat;
	int				process_num;
	int				*current_state;
	int				print_forbid;
	int				error;
	t_time			*prev_eat;
	t_time			start;

}					t_data;

int					ft_atoi(char *str);
char				*ft_itoa(int num);
int					ft_isdigit(char c);
int					ft_check_arguments(char **argv);
int					ft_fill_struct(t_data *philo, char **argv);
void				ft_philosophers_two(t_data *philo);
void				ft_success_exit(pid_t *pid, t_data *philo);
void				ft_error_exit(pid_t *pid, t_data *philo, int i);
void				*ft_philo_life(t_data *philo);
int					ft_sleep_think(t_data *philo, int i);
int					ft_check_fin_died(t_data *philo, int *eat_count);
int					ft_eating(t_data *philo, t_time *last_eat, \
												int *eat_count, int i);
int					ft_check_time(t_data *philo, struct timeval time, \
											t_time last_eat, int i);
int					ft_take_forks(t_data *philo, int i, t_time last_eat);
int					ft_take_left_right(t_data *philo, int i);
int					ft_print_status(t_data *philo, int i, int status);
void				ft_print_all(t_data *philo, char *milliseconds, \
										char *thread_number, int status);
void				ft_print_zeros(char *str);
int					ft_left_three(int num);
int					ft_count_digits(int num);
int					ft_check_if_died(t_data *philo);
int					ft_right(int n, int nof);
int					ft_left(int n, int nof);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
void				ft_putchar(char c);
void				ft_init_process(t_data *philo, struct timeval *time, \
															t_time *last_eat);
void				ft_get_thread_number(t_data *philo, int *i);
void				ft_fill_state_time(t_data *philo);
void				ft_start_init(t_data *philo);
void				ft_monitor_error_exit(t_data *philo);
void				*ft_monitor_life(void *philo);
void				*ft_scan_time(t_data *philo, struct timeval time);
void				ft_init_monitor_start_time(t_data *philo, t_time *start);
void				ft_init_semaphores(t_data *philo);
void				ft_destroy_semaphores(t_data *philo);
int					ft_mute_if_greedy(t_data *philo, t_time last_eat);

#endif
