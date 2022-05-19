#include "philo.h"

long long	milli_to_micro(int milliseconds)
{
	long long	microseconds;
	
	microseconds = milliseconds * 1000;
	return (microseconds);
}

int	error_msg(char *msg, int error_code)
{
	int	len;

	len = ft_strlen(msg);
	write(STDERR_FILENO, msg, len);
	return (error_code);
}

void	create_new_philo(t_philo *philo)
{
	philo->l_fork = false;
	philo->r_fork = false;
	philo->eating = false;
	philo->sleeping = false;
	philo->dead = false;
}

void	get_args(t_args *args, char *argv[])
{
	args->num_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->num_meals = ft_atoi(argv[5]);
	args->num_done_eating = 0;
	args->stop_simulation = false;
	pthread_mutex_init(&(args->stop_mutex), NULL);
	pthread_mutex_init(&(args->num_done_mutex), NULL);

}

void	init_philo(t_philo *philos, t_args *args)
{
	int	philo_index;
	
	philo_index = 0;
	while (philo_index < (*args).num_philos)
	{
		philos[philo_index].philo_index = philo_index;
		philos[philo_index].eaten_meals = 0;
		philos[philo_index].l_fork = 0;
		philos[philo_index].r_fork = 0;
		philos[philo_index].eating = 0;
		philos[philo_index].sleeping = 0;
		philos[philo_index].dead = 0;
		philos[philo_index].specs = args;
		philo_index++;
	}
}

pthread_mutex_t	*create_forks(int num)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(num * sizeof(pthread_mutex_t));
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(forks[i]), NULL);
		i++;
	}
	return (forks);
}

void	destroy_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	save_input(t_args *args, char *argv[], int argc)
{
	if (check_input(argc, argv))
		return (error_msg("expected usage: ./philo 3 200 100 150\n", 1));
	get_args(&args, argv);
	args->forks = create_forks(args->num_philos);
	return (0);
}