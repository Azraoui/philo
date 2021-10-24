/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:34:37 by ael-azra          #+#    #+#             */
/*   Updated: 2021/10/24 19:36:24 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

t_philos	*fill_philos(t_input *input)
{
	t_philos		*philos;
	pthread_mutex_t	*mutex;
	t_shared_info	*shared_info;
	int				*last_meal;
	int				i;

	shared_info = (t_shared_info *)malloc(sizeof(t_shared_info));
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * input->number_of_philo);
	philos = (t_philos *)malloc(sizeof(t_philos) * input->number_of_philo);
	last_meal = (int *)malloc(sizeof(int) * input->number_of_philo);
	for (int i = 0; i < input->number_of_philo; i++)
		last_meal[i] = 0;
	if (!philos || !shared_info || !mutex || !last_meal)
		return (NULL);
	i = 0;
	shared_info->fork_mutex = mutex;
	shared_info->last_meal = last_meal;
	shared_info->meal_count = 0;
	while (i < input->number_of_philo)
	{
		philos[i].philo_id = i;
		philos[i].time_to_die = input->time_to_die;
		philos[i].time_to_eat = input->time_to_eat;
		philos[i].time_to_sleep = input->time_to_sleep;
		philos[i].number_of_philo = input->number_of_philo;
		philos[i].number_of_time_to_eat = input->number_of_time_to_eat;
		philos[i].shared_info = shared_info;
		philos[i].eating = 0;
		philos[i].nb_meals = 0;
		pthread_mutex_init(&philos[i].wait_mutex, NULL);
		i++;
	}
	return (philos);
}

void	ft_print_output(int time, int id, char *str, t_philos *philos)
{
	pthread_mutex_lock(&philos[id].wait_mutex);
	printf("%d %d %s", time, id, str);
	if (strncmp(str, "dead\n", 5) == 0)
		exit(1);
	pthread_mutex_unlock(&philos[id].wait_mutex);
}

size_t gettime(struct timeval time_zero)
{
	size_t				time;
	size_t				s;
	struct timeval		last_time;

	gettimeofday(&last_time, NULL);
	s = (last_time.tv_sec - time_zero.tv_sec) * 1000;
	time = ((last_time.tv_usec - time_zero.tv_usec) / 1000) + s;
	return (time);
}

void	ft_usleep(size_t time)
{
	struct	timeval first_time;

	gettimeofday(&first_time, NULL);
	while ((gettime(first_time) * 1000) < time)
		usleep(200);
}

void	lock_forks(t_philos *philos, int id, struct timeval time_zero)
{
	// if (id == philos->number_of_philo)
	// {
	// 	for (int i = 0; i < philos->number_of_philo; i++)
	// 	{
	// 		if (((int)gettime(time_zero) - philos->shared_info->last_meal[i]) >= philos->time_to_die)
	// 		{
	// 			//printf("last meal = %d\n", philos->shared_info->last_meal[i]);
	// 			printf("%zu %d died\n", gettime(time_zero), i+1);
	// 			// printf("time = %d, eat = %d, time to die = %d\n", time, last_eat, philos->time_to_die);
	// 			exit(1);
	// 		}
	// 	}
	// 	return ;
	// }
	pthread_mutex_lock(&philos->shared_info->fork_mutex[id]);
	ft_print_output(gettime(time_zero), id + 1, "has taken a fork\n", philos);
	pthread_mutex_lock(&philos->shared_info->fork_mutex[(id + 1) % philos->number_of_philo]);
	ft_print_output(gettime(time_zero), id + 1, "has taken a fork\n", philos);
	
	ft_print_output(gettime(time_zero), id + 1, "is eating\n", philos);
	philos->eating = 1;
	ft_usleep(philos->time_to_eat * 1000);
	philos->shared_info->last_meal[id] = gettime(time_zero);
	philos->nb_meals++;
	philos->eating = 0;
	if (philos->nb_meals == philos->number_of_time_to_eat)
		philos->shared_info->meal_count++;
	pthread_mutex_unlock(&philos->shared_info->fork_mutex[id]);
	pthread_mutex_unlock(&philos->shared_info->fork_mutex[(id + 1) % philos->number_of_philo]);
	ft_print_output(gettime(time_zero), id + 1, "is sleeping\n", philos);
	ft_usleep(philos->time_to_eat * 1000);
	ft_print_output(gettime(time_zero), id + 1, "is thinking\n", philos);
}

void	*spaghetti_table(void *tmp)
{
	t_philos		*philos;
	struct	timeval first_time;

	philos = (t_philos *)tmp;
	gettimeofday(&first_time, NULL);
	if (philos->philo_id % 2)
		usleep(600);
	while (1)
	{
		lock_forks(philos, philos->philo_id, first_time);
		// if (philos->number_of_time_to_eat != -1)
		// {
		// 	philos->number_of_time_to_eat--;
		// 	if (philos->number_of_time_to_eat == 0)
		// 		exit(1);
		// }
	}
	return (NULL);
}

int	create_philo_threads(int size, t_philos *philos)
{
	int		i;
	pthread_t		*philo_threads;

	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!philo_threads)
		return (1);
	i = 0;
	while (i < size)
	{
		if (pthread_create(&philo_threads[i], NULL, &spaghetti_table, &philos[i]))
			return (1);
		i++;
	}
	i = 0;
	// while (i < size)
	// 	if (pthread_join(philo_threads[i++], NULL))
	// 		return (1);
	return (0);
}

void	threads_philo(t_input *input)
{
	t_philos		*philos;
	int				i;
	struct	timeval first_time;
	gettimeofday(&first_time, NULL);

	philos = fill_philos(input);
	if (!philos)
		return ;
	i = 0;
	while (i < input->number_of_philo)
		pthread_mutex_init(&philos->shared_info->fork_mutex[i++], NULL);
	create_philo_threads(input->number_of_philo, philos);
	i = 0;
	size_t last_meal;
	while (1)
	{
		i = 0;
		while (i < input->number_of_philo)
		{
			last_meal = philos[i].shared_info->last_meal[i];
				//printf("time = %zu, last_meal= %zu, time_to_die = %d\n", gettime(first_time), last_meal, philos[i].time_to_die);
			if (philos[i].eating == 0 && (int)(gettime(first_time) - last_meal) >= philos[i].time_to_die)
			{
				ft_print_output(gettime(first_time), i + 1, "dead\n", philos);
				return ;
			}
			if (philos->shared_info->meal_count == philos[i].number_of_philo)
				return ;
			i++;
		}
	}
	i = 0;
	while (i < input->number_of_philo)
	{
		pthread_mutex_destroy(&philos->shared_info->fork_mutex[i++]);
		pthread_mutex_destroy(&philos[i].wait_mutex);
	}
}

int	main(int ac, char *av[])
{
	t_input	*input;

	if (ac == 5 || ac == 6)
	{
		input = read_input(ac, av);
		if (!input)
		{
			printf("Error\n");
			return (1);
		}
		else
		{
			threads_philo(input);
			free(input);
			return (0);
		}
	}
	printf("Error\n");
	return (1);
}
