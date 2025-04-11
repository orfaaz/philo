/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_routines02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:55:09 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:11 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd(" is thinking\n", 1);
	}
	pthread_mutex_unlock(&data->print_mtx);
}

void	death_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	pthread_mutex_lock(&data->is_dead_mtx);
	if (!data->is_dead)
	{
		data->is_dead = 1;
		display_time(data);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd(" died\n", 1);
	}
	pthread_mutex_unlock(&data->is_dead_mtx);
	pthread_mutex_unlock(&data->print_mtx);
}
