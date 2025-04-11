/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_lstfct_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:54:39 by agamay            #+#    #+#             */
/*   Updated: 2025/04/11 12:54:42 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//creates a philo by initializing a thread (the philo) 
//and a mutex (the fork).
t_philo	*ph_lstnew(t_data *data, int n)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		free_all(data, 1);
	ft_memset(new, 0, sizeof(t_philo));
	if (pthread_create(&new->id, NULL, &start_routine, new))
	{
		ft_putstr_fd("thread creation failed", 2);
		free_all(data, 1);
	}
	if (pthread_mutex_init(&new->fork_mtx, NULL))
	{
		ft_putstr_fd("mutex creation failed", 2);
		free_all(data, 1);
	}
	new->data = data;
	new->n = n;
	new->meals = 0;
	new->next = NULL;
	return (new);
}

t_philo	*ph_lstlast(t_philo *lst)
{
	t_philo	*head;

	if (!lst)
		return (NULL);
	head = lst;
	while (lst->next != head)
		lst = lst->next;
	return (lst);
}

int	ph_lstsize(t_philo *lst)
{
	t_philo	*head;
	int		i;

	if (!lst)
		return (0);
	i = 0;
	head = lst;
	while (lst->next != head)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ph_lstadd_back(t_philo	**lst, t_philo *new)
{
	t_philo	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = new;
		return ;
	}
	last = ph_lstlast(*lst);
	last->next = new;
	new->next = *lst;
}

void	ph_lstclear(t_philo *lst, int lstsize)
{
	t_philo	*tmp;

	if (!lst)
		return ;
	lstsize++;
	while (lstsize--)
	{
		tmp = lst;
		pthread_mutex_destroy(&lst->fork_mtx);
		lst = lst->next;
		free(tmp);
	}
}
