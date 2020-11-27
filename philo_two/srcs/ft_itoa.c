/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 10:05:57 by mondrew           #+#    #+#             */
/*   Updated: 2020/11/12 20:31:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_digits(int nbr)
{
	int digits;

	if (nbr == -2147483648)
		return (11);
	digits = 0;
	if (nbr < 0)
	{
		digits++;
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		nbr = nbr / 10;
		digits++;
	}
	digits++;
	return (digits);
}

static void	ft_help(char *str, int digits, int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			str[1] = '2';
			n = -147483648;
		}
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
	{
		str[digits - 1] = '0';
		return ;
	}
	while (n > 0 || (digits == 1 && n == 0 && str[digits - 1] != '-'))
	{
		str[digits-- - 1] = n % 10 + 48;
		n = n / 10;
	}
}

char		*ft_itoa(int n)
{
	char	*str;
	int		digits;

	digits = ft_count_digits(n);
	str = malloc(sizeof(char) * (digits + 1));
	if (str == NULL)
		return (NULL);
	str[digits] = '\0';
	ft_help(str, digits, n);
	return (str);
}
