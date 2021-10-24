		if (philos->eating == 0 && gettime(first_time) - (unsigned int)die > (unsigned int)philos->time_to_die)
		{
			ft_print_output(gettime(first_time), philos->philo_id + 1, "died\n", philos);
			// printf("%d: %d died\n", gettime(first_time), philos->philo_id);
			philos->shared_info->philo_die = 1;
			exit(1);
		}
		// lock_fork(philos, &philos->shared_info->fork_mutex[philos->philo_id], gettime(first_time), philos->philo_id);
		// lock_fork(philos, &philos->shared_info->fork_mutex[(philos->philo_id + 1) % philos->number_of_philo], gettime(first_time), philos->philo_id);
		pthread_mutex_lock(&philos->shared_info->fork_mutex[philos->philo_id]);
		printf("%d %d has taken a fork\n", gettime(first_time), philos->philo_id + 1);
		pthread_mutex_lock(&philos->shared_info->fork_mutex[(philos->philo_id + 1) % philos->number_of_philo]);
		printf("%d %d has taken a fork\n", gettime(first_time), philos->philo_id + 1);
		ft_print_output(gettime(first_time), philos->philo_id + 1, "is eating\n", philos);
		// printf("%d: %d is eating\n", gettime(first_time), philos->philo_id);
		philos->eating = 1;
		ft_usleep(philos->time_to_eat * 1000);
		die = gettime(first_time);
		philos->eating = 0;
		pthread_mutex_unlock(&philos->shared_info->fork_mutex[philos->philo_id]);
		pthread_mutex_unlock(&philos->shared_info->fork_mutex[(philos->philo_id + 1) % philos->number_of_philo]);
		ft_print_output(gettime(first_time), philos->philo_id + 1, "is sleeping\n", philos);
		// printf("%d: %d is sleeping\n", gettime(first_time), philos->philo_id);
		ft_usleep(philos->time_to_sleep * 1000);
		ft_print_output(gettime(first_time), philos->philo_id + 1, "is thinking\n", philos);
		// printf("%d: %d is thinking\n", gettime(first_time), philos->philo_id);