#include "philosophers.h"

//checks if all values are valid. atoi them and stores in t_data.
void	parser(t_data *data, int ac, char **av)
{
	data->n_of_phi = ft_atoi(av[1]);
	data->lifetime = ft_atoi(av[2]);// * 1000
	data->eat_time = ft_atoi(av[3]) * 1000;
	data->sleep_time = ft_atoi(av[4]) * 1000;
	if (ac == 6)
	data->rounds = ft_atoi(av[5]);
	if (data->n_of_phi < 1 || data->lifetime < 10
			|| data->eat_time < 10 || data->sleep_time < 10)
	{
		ft_putstr_fd("args must be positive int", 2);
		free_all(data, 1);
	}
}
