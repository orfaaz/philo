/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:55:16 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:32 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

long long int	ft_llabs(long long int n)
{
	if (n < 0)
		return (-n);
	return (n);
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

void	invalid_argument(t_data *data, int eval)
{
	ft_putstr_fd("invalid arguments\n", 2);
	free_all(data, eval);
}

void	free_all(t_data *data, int code)
{
	if (!data)
		exit(1);
	ph_lstclear(data->philo_lst, ph_lstsize(data->philo_lst));
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->is_dead_mtx);
	free(data);
	exit(code);
}

//cheks if philo will die in sleep. adapts sleep time.
void	ft_usleep(t_data *data, t_philo *philo, long int len)
{
	long long int	time;

	gettimeofday(data->s_time, NULL);
	time = ((data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000)
			- data->strt_time) - philo->last_meal;
	if (time + len > data->lifetime - 2)
	{
		usleep(ft_llabs(data->lifetime - time) * 1000);
		death_routine(data, philo);
	}
	else
		usleep(len * 1000);
}
