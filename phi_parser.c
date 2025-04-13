/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:54:46 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:54:47 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//checks if all values are valid. atoi them and stores in t_data.
//lifetime will be a long, eat time and sleep time long long.
void	parser(t_data *data, int ac, char **av)
{
	data->n_of_phi = ft_atoi(av[1]);
	data->lifetime = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]) * 1000;
	data->sleep_time = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		data->rounds = ft_atoi(av[5]);
	else
		data->rounds = 4294967295;
	if (data->n_of_phi < 1 || data->lifetime < 10
		|| data->eat_time < 10 || data->sleep_time < 10)
	{
		write(1, "args must be positive int\n", 26);
		free_all(data, 1);
	}
}
