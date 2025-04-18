/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_utils02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:55:37 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:38 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	display_time(t_data *data)
{
	gettimeofday(data->s_time, NULL);
	data->time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000
		- data->strt_time;
	ft_putnbr_fd(data->time, 1);
	write(1, " ", 1);
}

long long int	ft_llabs(long long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//will return 1 if a philo died.
int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->is_dead_mtx);
	if (data->is_dead)
	{
		pthread_mutex_unlock(&data->is_dead_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->is_dead_mtx);
	return (0);
}
