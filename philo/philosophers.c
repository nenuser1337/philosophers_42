/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:05:36 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 09:06:32 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(200);
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	data = malloc(sizeof(t_data));
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	if (ac == 6)
		data->should_eat = ft_atoi(av[5]);
	else
		data->should_eat = -1;
	data->has_eaten = 0;
	data->n_philos = ft_atoi(av[1]);
	data->dead = 0;
	data->forks = malloc(sizeof(t_data) * data->n_philos);
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n_philos);
	while (i < data->n_philos)
	{
		philo[i].id = i;
		philo[i].lastt_lunch = get_time();
		philo[i].data = data;
		i++;
	}
	data->t_start = get_time();
	return (philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (check_error(ac, av) != 0)
		return (0);
	data = init_data(ac, av);
	philo = init_philo(data);
	creation_threads(data, philo);
}
