#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <sys/time.h>

#define AVAILABLE 1
#define TAKEN 0

typedef struct s_args
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_meals;
	int		num_done_eating;
	bool	stop_simulation;
	pthread_mutex_t	*forks;
}		t_args;

typedef struct s_philo
{
	int		philo_index;
	int		eaten_meals;
	bool	l_fork;
	bool	r_fork;
	bool	eating;
	bool	sleeping;
	bool	dead;
	t_args	*specs;
}		t_philo;



// let every fork be a mutex itself, not an int protected by a mutex
typedef struct s_fork
{
	bool	fork_status;
	// mutex;
}	t_fork;

int		check_input(int argc, char **input);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);

#endif