#include "philosophers.h"

int		ft_mute_if_greedy(void *philo, int i)
{
	int		n;
	int		a;

	n = 0;
	a = 0;
	while (n < ((t_data *)philo)->number_of_philosophers)
	{
		if (n == i)
			;
		else if (((t_data *)philo)->eat_times[i] > \
									((t_data *)philo)->eat_times[n])
			a++;
		n++;
	}
	if (a >= (((t_data *)philo)->number_of_philosophers / 2))
		return (1);
	return (0);
}
