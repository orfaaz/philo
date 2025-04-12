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

#include "philosophers.h"

void	display_time(t_data *data)
{
	pthread_mutex_lock(&data->get_time);
	gettimeofday(data->s_time, NULL);
	data->time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000
		- data->strt_time;
	ft_putstr_fd("|| ", 1);
	ft_putnbr_fd(data->time, 1);
	ft_putstr_fd(" || ", 1);
	pthread_mutex_unlock(&data->get_time);
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

int	check_hunger(t_data *data, t_philo *philo)
{
	long long int	time;

	pthread_mutex_lock(&data->get_time);
	gettimeofday(data->s_time, NULL);
	time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000
		- data->strt_time;
	if (time - philo->last_meal > data->lifetime)
	{
		pthread_mutex_unlock(&data->get_time);
		death_routine(data, philo);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->get_time);
	return (0);
}
