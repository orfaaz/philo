#include "philosophers.h"

void	invalid_argument(t_data *data, int eval)
{
	ft_putstr_fd("invalid arguments", 2);
	free_all(data, eval);
}

void	free_all(t_data *data, int code)
{
	if (!data)
		exit(1);
	ph_lstclear(data->philo_lst, ph_lstsize(data->philo_lst));
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->is_dead_mtx);
	free(data);
	exit(code);
}

void	display_time(t_data *data)
{
	long long int	time;

	gettimeofday(data->time, NULL);
	time = data->time->tv_sec * 1000 + data->time->tv_usec / 1000;
	ft_putstr_fd("|| ", 1);
	ft_putnbr_fd(time - data->strt_time, 1);
	ft_putstr_fd(" ||", 1);
}
