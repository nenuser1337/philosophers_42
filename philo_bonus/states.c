/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:35:21 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 18:47:18 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleeping(unsigned long duree, t_philo *philo)
{
	unsigned long	current;

	(void)philo;
	current = get_time();
	while (get_time() - current < duree)
	{
		usleep(200);
	}
}

void	print_msg(char *str, t_philo *philo)
{
	sem_wait(philo->data->printing);
	printf("%llu %d %s\n", (get_time() - philo->data->t_start), philo->id, str);
	sem_post(philo->data->printing);
}

t_data	*semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/printing");
	sem_unlink("/death");
	sem_unlink("/last_lunch");
	data->forks = sem_open("/forks", O_CREAT, 0600, data->n_philos);
	data->death = sem_open("/death", O_CREAT, 0600, 1);
	data->printing = sem_open("/printing", O_CREAT, 0600, 1);
	data->last_lunch = sem_open("/last_lunch", O_CREAT, 0600, 1);
	return (data);
}
