#include "philosophers.h"

int		ft_left(int n, int nof)
{
	int		left;

	left = (n - 1 + nof) % nof;
	return (left);
}

int		ft_right(int n, int nof)
{
	int		right;

	right = (n + 1) % nof;
	return (right);
}

int		ft_count_digits(int num)
{
	int		i;

	i = 1;
	while (num > 9)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int		ft_left_three(int num)
{
	int		i;

	i = ft_count_digits(num);
	while (i > 3)
	{
		num = num / 10;
		i--;
	}
	return (num);
}

void	ft_print_zeros(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i < 3)
	{
		ft_putchar('0');
		i++;
	}
}
