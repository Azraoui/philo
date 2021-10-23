/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:35:40 by ael-azra          #+#    #+#             */
/*   Updated: 2021/10/23 18:41:53 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_input
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_to_eat;
}				t_input;

typedef struct	s_shared_info
{
	int				philo_die;
	pthread_mutex_t	*fork_mutex;
	
}				t_shared_info;

typedef	struct	s_philos
{
	int		philo_id;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_philo;
	int		number_of_time_to_eat;
	int		eating;
	pthread_mutex_t	wait_mutex;
	t_shared_info		*shared_info;
}				t_philos;

t_input	*read_input(int ac, char *av[]);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);

#endif