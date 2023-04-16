/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:08:27 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 10:30:28 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_digit(str[i]) && str[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_error(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 6 && ac != 5)
		return (printf("Error : incorrect number of args! \n"), 1);
	if (!(atoi(av[1]) >= 1 && atoi(av[1]) <= 200))
		return (printf("Error : inaccurate number of philosophers!\n"), 1);
	while (av[i] != NULL)
	{
		if (is_number(av[i++]))
			return (printf("Error : incorrect input!\n"), 1);
	}
	return (0);
}

void	deallocate(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo[0].data->forks)
		free(philo[0].data->forks);
	if (philo[0].data)
		free(philo[0].data);
	if (philo)
		free(philo);
}

void	ft_clear(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->n_philos)
	{
		pthread_mutex_destroy(&philo[0].data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo[0].data->death);
	pthread_mutex_destroy(&philo[0].data->printing);
	pthread_mutex_destroy(&philo[0].data->last_lunch);
	pthread_mutex_destroy(&philo[0].data->eatmax);
	deallocate(philo);
}
