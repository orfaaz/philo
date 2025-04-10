#include "philosophers.h"

//creates n philos, and waits for them.
void	create_philos(t_data *data)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	gettimeofday(data->s_time, NULL);
	pthread_mutex_lock(&data->wait_start);
	while (++i <= data->n_of_phi)
		ph_lstadd_back(&data->philo_lst, ph_lstnew(data, i));
	data->strt_time = data->s_time->tv_sec * 1000 + data->s_time->tv_usec / 1000;
	pthread_mutex_unlock(&data->wait_start);
	philo = data->philo_lst;
	while (--i)
	{
		pthread_join(philo->id, NULL);
		pthread_mutex_lock(&data->print_mtx);
		// ft_putstr_fd("philo [", 2);
		// ft_putnbr_fd(philo->n, 2);
		// ft_putstr_fd("] joined\n", 2);
		pthread_mutex_unlock(&data->print_mtx);
		philo = philo->next;
	}
	pthread_mutex_destroy(&data->wait_start);
}

t_data	*data_init(struct timeval *s_time)
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
	errnum = pthread_mutex_init(&data->get_time, NULL);
	if (errnum)
		free_all(data, errnum);
	errnum = pthread_mutex_init(&data->wait_start, NULL);
	if (errnum)
		free_all(data, errnum);
	return (data);
}

//av: n_of_philo, time_to_die, time_to_eat, time_to_sleep
//[number_of_times_each_philosopher_must_eat]
int	main(int ac, char **av)
{
	t_data			*data;
	struct timeval	s_time;

	if (!(5 <= ac && ac <= 6))
		invalid_argument(NULL, 1);
	data = data_init(&s_time);
	parser(data, ac, av);
	create_philos(data);
	free_all(data, 0);
}
