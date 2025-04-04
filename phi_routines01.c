#include "philosophers.h"

static void	take_fork(t_data *data,t_philo *philo, pthread_mutex_t *fork_mtx)
{
	pthread_mutex_lock(fork_mtx);
	pthread_mutex_lock(&data->print_mtx);
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] has taken a fork\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
}

//philo takes own fork (right) and next fork (left),
//locks them for eat_time, before unlocking both.
static void	eat_routine(t_data *data, t_philo *philo)
{
	//!\case w/ odd number of philos this wont work.
	if (check_death(data))
		return ;
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
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] is eating\n", 1);
	philo->last_meal = data->time;
	pthread_mutex_unlock(&data->print_mtx);
	philo->meals++;
	usleep(data->eat_time);
	pthread_mutex_unlock(&philo->fork_mtx);
	pthread_mutex_unlock(&philo->next->fork_mtx);
}

void	sleep_routine(t_data *data, t_philo *philo)
{
	if (check_death(data))
		return ;
	pthread_mutex_lock(&data->print_mtx);
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] is sleeping\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
	usleep(data->sleep_time);
}

void	think_routine(t_data *data, t_philo *philo)
{
	if (check_death(data))
		return ;
	pthread_mutex_lock(&data->print_mtx);
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] is thinking\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
}

//ft called by pthread_create(); in ph_lstnew();.
void	*start_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = (t_data *)((t_philo *)philo)->data;
	while (!check_death(data) && philo->meals <= data->rounds)
	{
		eat_routine(data, philo);
		// usleep(100);
		sleep_routine(data, philo);
		// usleep(100);
		think_routine(data, philo);
		// usleep(100);
		check_hunger(data, philo);
	}
	return (NULL);
}
