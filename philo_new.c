#include "philo.h"

int	left_fork_index(t_philo philo)
{
	int	index;

	if (philo.philo_index == 0)
		index = philo.specs->num_philos - 1;
	else
		index = philo.philo_index - 1;
	return (index);
}

int	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->specs->eating_mutex));
	if (philo->eaten_meals == philo->specs->num_meals)
	{
		philo->specs->num_done_eating++;
		if (philo->specs->num_done_eating == philo->specs->num_philos)
		{
			philo->specs->stop_simulation = true;
			printf("All philosophers have had enough meals.\n");
			return (1);
		}
	}
	// eat
	pthread_mutex_lock(&philo->specs->forks[left_fork_index(*philo)]); // left fork
	pthread_mutex_lock(&philo->specs->forks[philo->philo_index]); // right fork

	if (philo->eaten_meals >= philo->specs->num_meals)
	{
		if (philo->specs->num_done_eating >= philo->specs->num_philos)
		{
			philo->specs->stop_simulation = true;
			printf("All philosophers have had enough meals.\n");
			pthread_mutex_unlock(&philo->specs->forks[left_fork_index(*philo)]); // left fork
			pthread_mutex_unlock(&philo->specs->forks[philo->philo_index]); // right fork
			return (1);
		}
	}
	philo->eaten_meals++;
	printf("THREAD %d: Will be eating %dst meal for %d milliseconds.\n", philo->philo_index, philo->eaten_meals, philo->specs->time_to_eat);
	pthread_mutex_unlock(&(philo->specs->eating_mutex));
	
	usleep(milli_to_micro(philo->specs->time_to_eat));
	pthread_mutex_unlock(&philo->specs->forks[left_fork_index(*philo)]); // left fork
	pthread_mutex_unlock(&philo->specs->forks[philo->philo_index]); // right fork
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	printf("THREAD %d: Will be sleeping for %d milliseconds.\n", philo->philo_index, philo->specs->time_to_sleep);
	usleep(milli_to_micro(philo->specs->time_to_sleep));
	return (0);
}

void *routine(void *arg){
	// philosopher comes to life
	t_philo *philo;

	philo = arg;
	printf("\nTHREAD %d: Started.\n", philo->philo_index);

	while (!philo->specs->stop_simulation)
	{
		eat_philo(philo);
		if (!philo->specs->stop_simulation)
			sleep_philo(philo);
		// think_philo(philo);
	}

	// philosopher dies
	printf("THREAD %d: Ended.\n\n", philo->philo_index);
	return NULL;
}

void	*monitoring_routine(void *arg)
{
	// check  
	return ;
}


int monitoring_thread(pthread_t *threads, t_philo *philos)
{
	int	result_code;

	result_code = pthread_create(&threads[0], NULL, monitoring_routine, &(philos[0]));
	if (!result_code)
		return (-1);
	return (1);
}

int main(int argc, char *argv[])
{
	t_args	args;
	int		result_code;
	int		philo_index;
	pthread_t	threads[args.num_philos + 1];
	// create philosophers with specs
	t_philo		philos[args.num_philos];

	if (save_input(&args, argv, argc))
		return (1);
	init_philo(philos, &args);
	philo_index = monitoring_thread_create(&threads, philos);

	// start simulation
	while (philo_index < args.num_philos && philo_index > 0)
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
	return (0);
}

/* 
TO DO: 

mutexes maken voor de forks
zorgen dat iedereen die forks kan zien
beginnen met simulatie

data race bij stop_simulation var oplossen

gettimeofday functie

 */