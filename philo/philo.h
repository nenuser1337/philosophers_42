/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-oul <yait-oul@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:07:36 by yait-oul          #+#    #+#             */
/*   Updated: 2023/04/16 10:51:27 by yait-oul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int					t_todie;
	unsigned long		t_tosleep;
	unsigned long		t_toeat;
	unsigned long		t_start;
	int					n_philos;
	int					has_eaten;
	int					ate;
	int					eating;
	int					dead;
	int					should_eat;
	int					alive;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
	pthread_mutex_t		printing;
	pthread_mutex_t		last_lunch;
	pthread_mutex_t		eatmax;

}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	t_data				*data;
	unsigned long long	lastt_lunch;
	char				*str;

}						t_philo;

int						error(char *str, t_data *data);
u_int64_t				get_time(void);
void					ft_usleep(unsigned long time);
void					*routine(void *ag);

void					sleeping(t_data *data);
int						eating(t_philo *philo);
void					malloc_it(t_philo *philo, t_data data);
int						creation_threads(t_data *data, t_philo *philo);
void					init_philos(t_philo **ph, t_data **data);
void					see_if_dead(t_philo *philo);
int						philo_sleeping(unsigned long duree, t_philo *philo);
int						print_msg(char *str, t_philo *philo);
int						thinking(t_philo *philo);
void					ft_clear(t_philo *philo);
void					deallocate(t_philo *philo);
int						ft_atoi(char *str);
int						check_error(int ac, char **av);
int						is_dead(t_philo *philo, int i);
void					to_sleep(t_philo *philo);
void					detaching_threads(t_philo *philo, t_data *data);
#endif