#include "philosophers.h"

void	death_routine(t_data *data, t_philo *philo)
{
	if (check_death(data))
		return ;
	pthread_mutex_lock(&data->is_dead_mtx);
	pthread_mutex_lock(&data->print_mtx);
	data->is_dead = 1;
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] died\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
	pthread_mutex_unlock(&data->is_dead_mtx);
}
