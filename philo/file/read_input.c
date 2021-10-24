/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:09:56 by ael-azra          #+#    #+#             */
/*   Updated: 2021/10/24 18:55:11 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	overflow_check(unsigned int res, int sign)
{
	if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1))
		return (1);
	return (0);
}

int	strtoint(char *str, int *status)
{
	int				i;
	int				len;
	int				sign;
	unsigned int	res;

	len = ft_strlen(str);
	res = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		*status = 1;
		return (0);
	}
	while (i < len)
	{
		res = res * 10 + str[i] - 48;
		if (!ft_isdigit(str[i]) || overflow_check(res, sign))
		{
			*status = 1;
			return (0);
		}
		i++;
	}
	return (res * sign);
}

t_input	*cheack_error(int ac, char *av[], t_input **input)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (i < ac)
	{
		strtoint(av[i], &status);
		if (status || (*input)->number_of_philo == 0)
		{
			free(*input);
			return (NULL);
		}
		i++;
	}
	return (*input);
}

t_input	*read_input(int ac, char *av[])
{
	t_input	*input;

	input = (t_input *)malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->number_of_philo = atoi(av[1]);
	input->time_to_die = atoi(av[2]);
	input->time_to_eat = atoi(av[3]);
	input->time_to_sleep = atoi(av[4]);
	input->number_of_time_to_eat = -1;
	if (ac == 6)
		input->number_of_time_to_eat = atoi(av[5]);
	return (cheack_error(ac, av, &input));
}
