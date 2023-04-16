/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:06:45 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 10:43:30 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleeping(unsigned long duree, t_philo *philo)
{
	unsigned long	current;

	current = get_time();
	while (get_time() - current < duree)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->death);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->death);
		usleep(200);
	}
	return (0);
}

int	print_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->printing);
	printf("%llu %d %s\n", (get_time() - philo->data->t_start), philo->id + 1,
		str);
	pthread_mutex_unlock(&philo->data->printing);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
			|| *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		if (res < 1 || res > 2147483647)
			return (printf("Error : incorrect input!\n"), 1);
		++str;
	}
	return (res * negative);
}
