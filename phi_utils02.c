#include "philosophers.h"

void	display_time(t_data *data)
{
	gettimeofday(data->s_time, NULL);
	data->time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000
		- data->strt_time;
	ft_putstr_fd("|| ", 1);
	ft_putnbr_fd(data->time, 1);
	ft_putstr_fd(" || ", 1);
}

//returns 1 if philo died from hunger.
int	check_hunger(t_data *data, t_philo *philo)
{
	gettimeofday(data->s_time, NULL);
	data->time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000
		- data->strt_time;
	if (data->time - philo->last_meal >= data->lifetime)
		death_routine(data, philo);
	else
		return (0);
	return (1);
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
