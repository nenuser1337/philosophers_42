/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:35:14 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 18:48:27 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_monitoring(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (philo->data->dead == 0)
	{
		usleep(100);
		sem_wait(philo->data->last_lunch);
		if ((int)(get_time() - (philo->lastt_lunch)) >= (philo->data->t_todie))
		{
			sem_post(philo->data->last_lunch);
			philo->data->dead = 1;
			sem_wait(philo->data->printing);
			printf("%llu %d died\n", (get_time() - philo->data->t_start),
				philo->id);
			exit(0);
		}
		sem_post(philo->data->last_lunch);
	}
	exit(0);
}

void	eating(t_philo *philo, int i)
{
	pthread_t	death;

	(void)i;
	pthread_create(&death, NULL, &thread_monitoring, philo);
	while (1)
	{
		print_msg("is thinking", philo);
		sem_wait(philo->data->forks);
		print_msg("has taken a fork", philo);
		sem_wait(philo->data->forks);
		print_msg("has taken a fork", philo);
		print_msg("is eating", philo);
		sem_wait(philo->data->death);
		philo->lastt_lunch = get_time();
		sem_post(philo->data->death);
		philo_sleeping(philo->data->t_toeat, philo);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_msg("is sleeping", philo);
		philo_sleeping(philo->data->t_tosleep, philo);
	}
	pthread_join(philo->monitor, NULL);
}

void	exit_philo(t_philo **philo)
{
	t_philo	*ptr;
	int		i;

	ptr = *philo;
	i = 0;
	while (i < ptr->data->n_philos)
	{
		i = -1;
		while (++i < ptr->data->n_philos)
			kill(ptr[i].process, SIGTERM);
		break ;
	}
	sem_close(ptr->data->printing);
	sem_close(ptr->data->forks);
	sem_close(ptr->data->death);
}
