#include "philosophers.h"

void	display_time(t_data *data)
{
	gettimeofday(data->time_s, NULL);
	data->time = data->time_s->tv_sec * 1000 + data->time_s->tv_usec / 1000
		- data->strt_time;
	ft_putstr_fd("|| ", 1);
	ft_putnbr_fd(data->time, 1);
	ft_putstr_fd(" ||", 1);
}

void	check_hunger(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	gettimeofday(data->time_s, NULL);
	ph_putnbr_fd(data->time - philo->last_meal, 2);
	ft_putstr_fd("<------ should die?\n", 2);
	pthread_mutex_unlock(&data->print_mtx);
	if (data->time - philo->last_meal > data->lifetime)
		death_routine(data, philo);
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
