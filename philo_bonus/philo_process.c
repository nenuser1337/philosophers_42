/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:35:18 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 18:39:26 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		data->should_eat = 5;
	else
		data->should_eat = -1;
	data->has_eaten = 0;
	data->n_philos = ft_atoi(av[1]);
	data->dead = 0;
	data = semaphores(t_data data);
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
		philo[i].id = i + 1;
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
	int		i;
	int		j;
	int		status;

	data = init_data(ac, av);
	philo = init_philo(data);
	i = 0;
	j = 0;
	while (i < data->n_philos)
	{
		philo[i].process = fork();
		if (philo[i].process == 0)
			eating(&philo[i], i);
		i++;
	}
	waitpid(-1, &status, 0);
	exit_philo(&philo);
	return (0);
}
