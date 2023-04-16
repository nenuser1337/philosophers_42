#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>


typedef struct s_data
{
	unsigned long long   t_todie;
    unsigned long  t_tosleep;
    unsigned long  t_toeat;
    unsigned long  t_start;
    int             n_philos;
    int             has_eaten;
    int             ate;
    int             eating;
    int             dead;
    int             should_eat;
    int             alive;
    sem_t *forks;
    sem_t *death;
    sem_t *printing;
    sem_t last_lunch;
    sem_t eatmax;
   
}t_data;

typedef struct s_philo
{
    pid_t       process;
    pthread_t   monitor;
    int        id;
    t_data      *data;
    unsigned long long lastt_lunch;
    char *str;
    
}  t_philo;

int			error(char *str, t_data *data);
u_int64_t	get_time(void);
void			ft_usleep(unsigned long time);
void 		*routine(void *ag);

void 		sleeping(t_data *data);
void	    eating(t_philo *philo, int i);
void        malloc_it(t_philo *philo, t_data data);
int         creation_threads(t_data *data, t_philo *philo);
void        init_philos(t_philo **ph , t_data **data);
int       see_if_dead(t_philo *philo);
void        philo_sleeping(unsigned long duree, t_philo *philo);
void          print_msg(char *str,  t_philo *philo);
int             thinking(t_philo *philo);
void ft_clear(t_philo *philo);
void  deallocate(t_philo *philo);
int	ft_atoi( char *str);
void forker(t_philo *philo, int nprocesses);
int creation_processes(t_data *data, t_philo *philo);
void child_process(t_philo *philo);
void	exit_philo(t_philo **philo);
#endif