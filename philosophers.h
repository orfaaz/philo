#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

//philosopher struct. philo is a thread, fork is a mutex.
typedef struct	s_philo
{
	pthread_t		id;
	int				n;
	pthread_mutex_t	fork_mtx;//right hand fork (left fork = next->fork)
	int				hunger;
	int				meals;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct	s_data
{
	unsigned int	n_of_phi;
	long int		lifetime;
	long int		eat_time;
	long int		sleep_time;
	unsigned int	rounds;
	t_philo			*philo_lst;
	struct timeval	*time;
	long long int	strt_time;
	pthread_mutex_t	is_dead_mtx;
	pthread_mutex_t	print_mtx;
}	t_data;

//routines
void	*start_routine(void *philo);
//parsing
void	parser(t_data *data, int ac, char **av);
//circular lst fct
t_philo	*ph_lstnew(t_data *data, int n);
int		ph_lstsize(t_philo *lst);
t_philo	*ph_lstlast(t_philo *lst);
void	ph_lstadd_back(t_philo	**lst, t_philo *new);
void	ph_lstclear(t_philo *lst, int size);
//utils
void	invalid_argument(t_data *data, int eval);
void	free_all(t_data *data, int code);
void	display_time(t_data *data);

#endif