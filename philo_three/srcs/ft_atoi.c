/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:18:08 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/12 18:56:14 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	nbr = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' ||
		*nptr == '\f' || *nptr == '\v' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + *(nptr++) - 48;
		if (sign > 0 && nbr > 9223372036854775807)
			return (-1);
		if (sign < 0 && nbr > 9223372036854775807)
			return (0);
	}
	return ((int)(nbr * sign));
}
