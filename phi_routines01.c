/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_routines01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:55:01 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:03 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//takes fork, then checks if philo sould starve.
static void	take_fork(t_data *data, t_philo *philo, pthread_mutex_t *fork_mtx)
{
	pthread_mutex_lock(fork_mtx);
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putnbr_fd(philo->n, 1);
		write(1, " has taken a fork\n", 18);
	}
	pthread_mutex_unlock(&data->print_mtx);
}

//philo takes own fork (right) and next fork (left)
static void	forks_routine(t_data *data, t_philo *philo)
{
	if (philo->n % 2)
	{
		take_fork(data, philo, &philo->fork_mtx);
		take_fork(data, philo, &philo->next->fork_mtx);
	}
	else
	{
		take_fork(data, philo, &philo->next->fork_mtx);
		take_fork(data, philo, &philo->fork_mtx);
	}
}

//if philo has 2 forks. eats then unlocks them.
static void	eat_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		philo->last_meal = data->time;
		ft_putnbr_fd(philo->n, 1);
		write(1, " is eating\n", 11);
	}
	philo->meals++;
	pthread_mutex_unlock(&data->print_mtx);
	if (!check_death(data))
		usleep(data->eat_time);
	pthread_mutex_unlock(&philo->next->fork_mtx);
	pthread_mutex_unlock(&philo->fork_mtx);
}

//philo will sleep for given time. Unless he starves in sleep.
static void	sleep_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putnbr_fd(philo->n, 1);
		write(1, " is sleeping\n", 13);
	}
	pthread_mutex_unlock(&data->print_mtx);
	if (!check_death(data))
		usleep(data->sleep_time);
}

//ft called by pthread_create(); in ph_lstnew();.
void	*start_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->wait_start);
	pthread_mutex_unlock(&data->wait_start);
	if (!philo->n % 2)
		usleep(100);
	while (!check_death(data) && philo->meals <= data->rounds
		&& philo->next != philo)
	{
		forks_routine(data, philo);
		eat_routine(data, philo);
		sleep_routine(data, philo);
		think_routine(data, philo);
	}
	if (philo->next == philo)
	{
		take_fork(data, philo, &philo->fork_mtx);
		usleep(data->lifetime);
		pthread_mutex_unlock(&philo->fork_mtx);
	}
	return (NULL);
}
