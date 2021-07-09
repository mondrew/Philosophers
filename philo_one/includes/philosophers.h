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
# include <sys/time.h>
# include <pthread.h>
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
	int				*current_state;
	int				*thread_num_array;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
	pthread_mutex_t	thread_number;
	pthread_mutex_t	printer;
	pthread_mutex_t	start_time;
	pthread_mutex_t	stop_all;
	pthread_mutex_t	error_mutex;
	t_time			start;
	int				*block_at_start;
	int				race_win;
	int				print_forbid;
	int				error;
	pthread_mutex_t	block_mutex;
	t_time			*prev_eat;
}					t_data;

int					ft_atoi(char *str);
char				*ft_itoa(int num);
int					ft_isdigit(char c);
int					ft_check_arguments(char **argv);
int					ft_fill_struct(t_data *philo, char **argv);
void				ft_philosophers_one(t_data *philo, int i);
void				ft_success_exit(pthread_t *pthread, pthread_t monitor, \
																t_data *philo);
void				ft_error_exit(pthread_t *pthread, pthread_t monitor, \
														t_data *philo, int i);
void				*ft_philo_life(void *philo);
int					ft_sleep_think(void *philo, int i);
int					ft_check_fin_died(void *philo, int *eat_count, int i);
int					ft_eating(void *philo, t_time *last_eat, \
												int *eat_count, int i);
int					ft_check_time(void *philo, struct timeval time, \
											t_time last_eat, int i);
int					ft_take_forks(void *philo, int i);
int					ft_take_left_right(void *philo, int i);
int					ft_print_status(void *philo, int i, int status);
void				ft_print_all(void *philo, char *milliseconds, \
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
void				ft_init_thread(void *philo, int *i, struct timeval *time, \
															t_time *last_eat);
void				ft_get_thread_number(void *philo, int *i);
void				ft_fill_state_time(t_data *philo);
void				ft_start_init(t_data *philo, int *thread_num_array, \
									int *block_at_start, t_time *prev_eat);
void				ft_monitor_error_exit(pthread_t monitor, t_data *philo);
void				ft_init_mutexes(t_data *philo);
void				*ft_monitor_life(void *philo);
void				*ft_scan_time(void *philo, struct timeval time);
void				ft_init_monitor_start_time(void *philo, t_time *start);
void				ft_destroy_mutexes(t_data *philo);

#endif
