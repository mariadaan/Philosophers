#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
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

void create_new_philo(t_philo *philo)
{
	philo->l_fork = false;
	philo->r_fork = false;
	philo->eating = false;
	philo->sleeping = false;
	philo->dead = false;
}

void *routine(void *arg){
	// philosopher comes to life
	t_philo *philo;

	// gettimeofday(); // hoe deze gebruiken??
	
	philo = arg;
	printf("\nTHREAD %d: Started.\n", philo->philo_index);
	printf("THREAD %d: Will be sleeping for %d milliseconds.\n", philo->philo_index, philo->specs.time_to_sleep);
	
	pthread_mutex_lock(&philo->specs.forks[philo->philo_index]);
	// while !dead (timestamp < timetodie)
		// eat
		// sleep(time_to_eat);
		// put forks back
		usleep(milli_to_micro(philo->specs.time_to_sleep));
		// find fork
			// loop until fork is found and !dead


	// philosopher dies
	printf("THREAD %d: Ended.\n\n", philo->philo_index);
	return NULL;
}


void get_args(t_args *args, char *argv[])
{
	args->num_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
}

void init_philo(t_philo *philos, t_args *args)
{
	int philo_index = 0;
	while (philo_index < (*args).num_philos)
	{
		philos[philo_index].philo_index = philo_index;
		philos[philo_index].l_fork = 0;
		philos[philo_index].r_fork = 0;
		philos[philo_index].eating = 0;
		philos[philo_index].sleeping = 0;
		philos[philo_index].dead = 0;
		philos[philo_index].specs = *args;
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

int main(int argc, char *argv[])
{
	t_args	args;
	int	result_code;
	int	philo_index;

	if (check_input(argc, argv))
		return (error_msg("expected usage: ./philo 3 200 100 150\n", 1));
	get_args(&args, argv);

	args.forks = create_forks(args.num_philos);

	// create amount of philosophers threads
	pthread_t threads[args.num_philos];

	// create philosophers with specs
	t_philo philos[args.num_philos];
	init_philo(philos, &args);

	// create threads and start simulation
	philo_index = 0;
	while (philo_index < args.num_philos)
	{
		printf("IN MAIN: Creating thread %d.\n", philo_index);
		result_code = pthread_create(&threads[philo_index], NULL, routine, &(philos[philo_index]));
		if (result_code)
			return(error_msg("error creating thread\n", 1));
		philo_index++;
	}

	printf("IN MAIN: All threads are created.\n");



	// wait for all threads to finish
	philo_index = 0;
	while (philo_index < args.num_philos)
	{
		pthread_join(threads[philo_index], NULL);
		philo_index++;
	}

	destroy_forks(args.forks, args.num_philos);

	// // The pthread_mutex_init() function creates a new mutex
	// pthread_mutex_init(&mutex, NULL);


	// //frees the resources allocated for mutex
	// pthread_mutex_destroy(&mutex);

	return (0);
}

/* 
TO DO: 

mutexes maken voor de forks
zorgen dat iedereen die forks kan zien
beginnen met simulatie

gettimeofday functie

 */