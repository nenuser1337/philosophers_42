/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:41:54 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 10:45:03 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].data->last_lunch);
	if ((int)(get_time() - (philo[i].lastt_lunch)) >= (philo[i].data->t_todie))
	{
		pthread_mutex_unlock(&philo[i].data->last_lunch);
		pthread_mutex_lock(&philo[i].data->death);
		philo[i].data->dead = 1;
		pthread_mutex_unlock(&philo[i].data->death);
		pthread_mutex_lock(&philo->data->printing);
		printf("%llu %d has died ...\n", (get_time() - philo->data->t_start),
			philo->id + 1);
		pthread_mutex_unlock(&philo->data->printing);
		ft_clear(philo);
		return (-1);
	}
	pthread_mutex_unlock(&philo[i].data->last_lunch);
	return (0);
}

void	to_sleep(t_philo *philo)
{
	philo_sleeping(philo->data->t_toeat, philo);
	pthread_mutex_unlock(&philo->data->forks[(philo->id)]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->n_philos]);
	print_msg("is sleeping", philo);
	philo_sleeping(philo->data->t_tosleep, philo);
}

void	detaching_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	see_if_dead(philo);
	while (i < data->n_philos)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
}
