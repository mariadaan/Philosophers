#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>

#define AVAILABLE 1
#define TAKEN 0

typedef struct s_philo
{
	bool	l_fork;
	bool	r_fork;
	bool	eating;
	bool	sleeping;
	bool	dead;
}		t_philo;

typedef struct s_args
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	bool	*forks;
}		t_args;

typedef struct s_fork
{
	bool	fork_status;
	// mutex;
}	t_fork;

int	check_input(int argc, char **input);

#endif