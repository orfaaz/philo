#include "philosophers.h"

//creates n philos, and waits for them.
void	create_philos(t_data *data)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	// gettimeofday(data->time, NULL);
	// data->strt_time = data->time->tv_sec * 1000 + data->time->tv_usec / 1000;
	while (++i <= data->n_of_phi)
		ph_lstadd_back(&data->philo_lst, ph_lstnew(data, i));
	philo = data->philo_lst;
	while (philo)
	{
		pthread_join(philo->id, NULL);
		philo = philo->next;
	}
}

t_data	*data_init()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->is_dead_mtx, NULL);
	return (data);
}

//av: n_of_philo, time_to_die, time_to_eat, time_to_sleep
//[number_of_times_each_philosopher_must_eat]
int	main(int ac, char **av)
{
	t_data			*data;
	// struct timeval	time;//.tv_sec, .tv_usec.

	if (!(5 <= ac && ac <= 6))
		invalid_argument(NULL, 1);
	data = data_init();
	// data->time = &time;
	parser(data, ac, av);
	create_philos(data);
}
