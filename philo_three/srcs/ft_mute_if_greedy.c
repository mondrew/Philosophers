/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mute_if_greedy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:52:58 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/26 21:25:51 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_mute_if_greedy(t_data *philo, t_time last_eat)
{
	struct timeval	time;
	int				starving_time;

	gettimeofday(&time, NULL);
	starving_time = (time.tv_sec - last_eat.sec) * 1000 + \
						(time.tv_usec - last_eat.usec) / 1000;
	if (starving_time > 10 && starving_time < (philo->time_to_die / 2))
		return (1);
	return (0);
}
