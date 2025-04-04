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
	ph_putnbr_fd(philo->last_meal, 2);//tmp
	ft_putstr_fd("<-----mealtime\n", 2);//tmp
	pthread_mutex_unlock(&data->print_mtx);
	usleep(data->eat_time);
	pthread_mutex_unlock(&philo->fork_mtx);
	pthread_mutex_unlock(&philo->next->fork_mtx);
	// tmp display vv
	pthread_mutex_lock(&data->print_mtx);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] let go of forks\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
}

void	sleep_routine(t_data *data, t_philo *philo)
{
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
	pthread_mutex_lock(&data->print_mtx);
	display_time(data);
	ft_putstr_fd("philo [", 1);
	ft_putnbr_fd(philo->n, 1);
	ft_putstr_fd("] is thinking\n", 1);
	pthread_mutex_unlock(&data->print_mtx);
}

//ft called by pthread_create(); in ph_lstnew();.
void	*start_routine(void *philo)
{
	t_data	*data;

	data = (t_data *)((t_philo *)philo)->data;
	while (!check_death(data))
	{
		eat_routine(data, philo);
		usleep(100);
		sleep_routine(data, philo);
		usleep(100);
		think_routine(data, philo);
		usleep(100);
		// check_hunger(data, philo);
	}
	return (NULL);//terminates thread.
}
