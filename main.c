/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:54:31 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:54:33 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_death(t_data *data, t_philo *philo, long long int time)
{
	pthread_mutex_lock(&data->is_dead_mtx);
	data->is_dead = 1;
	ft_putnbr_fd(time, 1);
	write (1, " ", 1);
	ft_putnbr_fd(philo->n, 1);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&data->is_dead_mtx);
}

//as soon as a philo starves, set is_dead at one.
static void	monitor(t_data *data, t_philo *philo)
{
	long long int	time;
	int				dead_philo;

	dead_philo = 0;
	while (!dead_philo)
	{
		pthread_mutex_lock(&data->print_mtx);
		pthread_mutex_lock(&data->get_time);
		gettimeofday(data->s_time, NULL);
		time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec
			/ 1000 - data->strt_time;
		if (time - philo->last_meal > data->lifetime)
		{
			dead_philo = 1;
			if (philo->meals < data->rounds)
				print_death(data, philo, time);
		}
		pthread_mutex_unlock(&data->get_time);
		pthread_mutex_unlock(&data->print_mtx);
		philo = philo->next;
		usleep(20);
	}
}

//creates n philos, and waits for them.
static void	create_philos(t_data *data, unsigned int i)
{
	t_philo			*philo;

	pthread_mutex_lock(&data->wait_start);
	while (++i <= data->n_of_phi)
		ph_lstadd_back(&data->philo_lst, ph_lstnew(data, i));
	i = 0;
	philo = data->philo_lst;
	while (++i <= data->n_of_phi)
	{
		pthread_create(&philo->id, NULL, &start_routine, philo);
		philo = philo->next;
	}
	gettimeofday(data->s_time, NULL);
	data->strt_time = data->s_time->tv_sec * 1000
		+ data->s_time->tv_usec / 1000;
	pthread_mutex_unlock(&data->wait_start);
	philo = data->philo_lst;
	monitor(data, philo);
	while (--i)
	{
		pthread_join(philo->id, NULL);
		philo = philo->next;
	}
	pthread_mutex_destroy(&data->wait_start);
}

static t_data	*data_init(struct timeval *s_time)
{
	t_data	*data;
	int		errnum;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->s_time = s_time;
	errnum = pthread_mutex_init(&data->print_mtx, NULL);
	if (errnum)
		free_all(data, errnum);
	errnum = pthread_mutex_init(&data->is_dead_mtx, NULL);
	if (errnum)
		free_all(data, errnum);
	errnum = pthread_mutex_init(&data->wait_start, NULL);
	if (errnum)
		free_all(data, errnum);
	errnum = pthread_mutex_init(&data->get_time, NULL);
	if (errnum)
		free_all(data, errnum);
	return (data);
}

int	main(int ac, char **av)
{
	t_data			*data;
	struct timeval	s_time;

	if (!(5 <= ac && ac <= 6))
		invalid_argument(NULL, 1);
	data = data_init(&s_time);
	parser(data, ac, av);
	create_philos(data, 0);
	free_all(data, 0);
}
