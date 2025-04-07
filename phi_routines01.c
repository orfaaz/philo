#include "philosophers.h"

static void	take_fork(t_data *data,t_philo *philo, pthread_mutex_t *fork_mtx)
{
	if (check_death(data))
		return ;
	pthread_mutex_lock(fork_mtx);
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putstr_fd("philo [", 1);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd("] has taken a fork\n", 1);
	}
	pthread_mutex_unlock(&data->print_mtx);
}

//philo takes own fork (right) and next fork (left),
//locks them for eat_time, before unlocking both.
static void	eat_routine(t_data *data, t_philo *philo)
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
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putstr_fd("philo [", 1);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd("] is eating\n", 1);
		philo->last_meal = data->time;
	}
	pthread_mutex_unlock(&data->print_mtx);
	philo->meals++;
	ft_usleep(data, philo, data->eat_time);
	pthread_mutex_unlock(&philo->fork_mtx);
	pthread_mutex_unlock(&philo->next->fork_mtx);
}

void	sleep_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putstr_fd("philo [", 1);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd("] is sleeping\n", 1);
	}
	pthread_mutex_unlock(&data->print_mtx);
	ft_usleep(data, philo, data->sleep_time);
}

void	think_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mtx);
	if (!check_death(data))
	{
		display_time(data);
		ft_putstr_fd("philo [", 1);
		ft_putnbr_fd(philo->n, 1);
		ft_putstr_fd("] is thinking\n", 1);
	}
	pthread_mutex_unlock(&data->print_mtx);
}

//ft called by pthread_create(); in ph_lstnew();.
void	*start_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = (t_data *)((t_philo *)philo)->data;
	pthread_mutex_lock(&data->wait_start);
	pthread_mutex_unlock(&data->wait_start);
	while (!check_death(data) && philo->meals <= data->rounds)
	{
		if (!check_death(data))
			eat_routine(data, philo);
		if (!check_death(data))
			sleep_routine(data, philo);
		if (!check_death(data))
			think_routine(data, philo);
	}
	// pthread_mutex_lock(&data->print_mtx);
	// ft_putstr_fd("philo [", 1);
	// ft_putnbr_fd(philo->n, 1);
	// ft_putstr_fd("] ended\n", 1);
	// pthread_mutex_unlock(&data->print_mtx);
	return (NULL);
}
