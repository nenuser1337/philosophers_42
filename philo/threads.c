/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:09:23 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 20:25:19 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		pthread_mutex_init(&philo[i].data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo[0].data->death, NULL);
	pthread_mutex_init(&philo[0].data->printing, NULL);
	pthread_mutex_init(&philo[0].data->last_lunch, NULL);
	pthread_mutex_init(&philo[0].data->eatmax, NULL);

	return (philo);
}

int	eating(t_philo *philo)
{
	
	print_msg("is thinking", philo);
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
		% philo->data->n_philos]);
	print_msg("has taken a fork", philo);
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
			% philo->data->n_philos]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[(philo->id)]);
	print_msg("has taken a fork", philo);
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->data->death);
	philo->data->has_eaten++;
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->last_lunch);
	philo->lastt_lunch = get_time();
	pthread_mutex_unlock(&philo->data->last_lunch);
	to_sleep(philo);
	return (0);
}

void	*routine(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		if (eating(philo))
			return (0);
	}
	return (NULL);
}

int	creation_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	philo = init_mutexes(philo);
	while (i < data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (3);
		i = i + 2;
		usleep(5);
	}
	i = 1;
	usleep(200);
	while (i < data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (2);
		i = i + 2;
	}
	detaching_threads(philo, data);
	return (0);
}

void	see_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_dead(philo, i) == -1)
			break ;
		pthread_mutex_lock(&philo[i].data->eatmax);
		if (philo[i].data->should_eat != -1
			&& philo[i].data->has_eaten >= (philo[i].data->should_eat
				* philo[i].data->n_philos))
		{
			pthread_mutex_unlock(&philo[i].data->eatmax);
			ft_clear(philo);
			break ;
		}
		pthread_mutex_unlock(&philo[i].data->eatmax);
		i = ((i + 1) % (philo->data->n_philos));
	}
}
