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

int	left_fork_index(t_philo philo)
{
	int	index;

	if (philo.philo_index == 0)
		index = philo.specs->num_philos - 1;
	else
		index = philo.philo_index - 1;
	return (index);
}

void	protected_change_int(pthread_mutex_t *mutex, int *old_val, int new_val)
{
	pthread_mutex_lock(mutex);
	*old_val = new_val;
	pthread_mutex_unlock(mutex);
}

void	protected_change_bool(pthread_mutex_t *mutex, bool *old_val, bool new_val)
{
	pthread_mutex_lock(mutex);
	*old_val = new_val;
	pthread_mutex_unlock(mutex);
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

	// gettimeofday(); // hoe deze gebruiken??
	
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


void get_args(t_args *args, char *argv[])
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

void init_philo(t_philo *philos, t_args *args)
{
	int philo_index = 0;
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