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

// static long long int	ft_llabs(long long int n)
// {
// 	if (n < 0)
// 		return (-n);
// 	return (n);
// }

void	think_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putnbr_fd(philo->n, 1);
		write(1, " is thinking\n", 13);
	}
	pthread_mutex_unlock(&data->print_mtx);
	usleep(50);
}
