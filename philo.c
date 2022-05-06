#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "philo.h"

// void *routine()
// {
// 	pthread_mutex_lock(&mutex);
// 	for (int i = 0; i < 1000000; i++){
// 		global++;
		
// 	}
// 	printf("%d ", global);
// 	pthread_mutex_unlock(&mutex);
// 	return NULL;
// }

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
	
	philo = arg;
	int index = philo->philo_index;
	int sleep_time = philo->specs.time_to_sleep;


	printf("\nindex: %d\n", index);
	printf("sleeptime: %d\n", sleep_time);

	printf("THREAD %d: Started.\n", index);
	printf("THREAD %d: Will be sleeping for %d milliseconds.\n", index, sleep_time);
	// while !dead (timestamp < timetodie)
		// eat
		// sleep(time_to_eat);
		// put forks back
		usleep(milli_to_micro(sleep_time));
		// find fork
			// loop until fork is found and !dead


	// philosopher dies
	printf("THREAD %d: Ended.\n\n", index);
	return NULL;
}


void get_args(t_args *args, char *argv[])
{
	args->num_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
}

void get_philo_specs(t_philo *philos, t_args args)
{
	int philo_index = 0;
	while (philo_index < args.num_philos)
	{
		philos[philo_index].philo_index = philo_index;
		philos[philo_index].specs = args;
		philo_index++;
	}

}

int main(int argc, char *argv[])
{
	t_args args;

	if (check_input(argc, argv))
		return (error_msg("expected usage: ./philo 3 200 100 150\n", 1));
	get_args(&args, argv);

	// create amount of philosophers threads
	pthread_t threads[args.num_philos];

	// create philosophers with specs
	t_philo philos[args.num_philos];
	get_philo_specs(philos, args);

	// int *thread_args = malloc(5 * sizeof(int));
	// // thread_args[0] = args.num_philo;
	// thread_args[1] = args.time_to_die;
	// thread_args[2] = args.time_to_eat;
	// thread_args[3] = args.time_to_sleep;
	// thread_args[4] = 0;

	// printf("die time : %d\n", thread_args[1]);
	// printf("eat time : %d\n", thread_args[2]);
	// printf("sleeptime: %d\n", thread_args[3]);

	int result_code;

	int philo_index = 0;
	while (philo_index < args.num_philos)
	{
		printf("\nphilo_index: %d\n", philo_index);

		printf("IN MAIN: Creating thread %d.\n", philo_index);
		result_code = pthread_create(&threads[philo_index], NULL, routine, &(philos[philo_index]));
		if (result_code)
		{
			printf("exit\n");
			exit(0);
		}
		philo_index++;
	}

	printf("IN MAIN: All threads are created.\n");



	// // The pthread_mutex_init() function creates a new mutex
	// pthread_mutex_init(&mutex, NULL);

	// // create threads
	// pthread_create(&t1, NULL, routine, NULL);
	// pthread_create(&t2, NULL, routine, NULL);

	// wait
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);

	// //frees the resources allocated for mutex
	// pthread_mutex_destroy(&mutex);

	return (0);
}
