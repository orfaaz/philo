#include "philosophers.h"
#include <limits.h>

void	ph_putnbr_fd(long long int nbr, int fd)
{
	if (fd < 0)
		return ;
	if (nbr == LLONG_MIN)
		write(1, "-9223372036854775807", 20);
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		ph_putnbr_fd(-nbr, fd);
	}
	else if (nbr > 9)
	{
		ph_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

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
