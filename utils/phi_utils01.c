/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:55:16 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:32 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*temp;

	temp = dest;
	while (n--)
		*temp++ = c;
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void	invalid_argument(t_data *data, int eval)
{
	write(1, "invalid arguments\n", 18);
	free_all(data, eval);
}

void	free_all(t_data *data, int code)
{
	if (!data)
		exit(1);
	ph_lstclear(data->philo_lst, ph_lstsize(data->philo_lst));
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->is_dead_mtx);
	pthread_mutex_destroy(&data->get_time);
	free(data);
	exit(code);
}
