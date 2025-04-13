/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_utils03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:55:14 by agamay            #+#    #+#             */
/*   Updated: 2025/04/12 13:55:18 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <limits.h>

static int	ft_isspace3(const char c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

int	ft_atoi(const char *nbr)
{
	int	sign;
	int	num;

	sign = 0;
	num = 0;
	while (ft_isspace3(*nbr))
		nbr++;
	if (*nbr == '-')
	{
		sign = 1;
		nbr++;
	}
	else if (*nbr == '+')
		nbr++;
	while (*nbr >= '0' && *nbr <= '9')
	{
		num = num * 10 + (*nbr - 48);
		nbr++;
	}
	if (sign == 1)
		return (-num);
	return (num);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putnbr_fd(int nbr, int fd)
{
	if (fd < 0)
		return ;
	if (nbr == -2147483648)
		write(1, "-2147483648", 11);
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nbr, fd);
	}
	else if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

void	ph_putnbr_fd(long long int nbr, int fd)
{
	if (fd < 0)
		return ;
	if (nbr == LLONG_MIN)
		write(1, "-9223372036854775807", 20);
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		ph_putnbr_fd(-nbr, fd);
	}
	else if (nbr > 9)
	{
		ph_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}
