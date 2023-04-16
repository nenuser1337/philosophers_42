#include "philo_bonus.h"

void *thread_monitoring(void *argv)
{
	t_philo *philo;

	philo = (t_philo*)argv;
	// printf("philo->id = %d \n\n", philo->id);
	while (philo->data->dead == 0)
	{
		usleep(100);
		if ((int)(get_time()- (philo->lastt_lunch)) >= (philo->data->t_todie))
		{
			
			
			philo->data->dead = 1;
			sem_wait(philo->data->printing);
			printf("%llu %d has died ...\n", (get_time()
						- philo->data->t_start), philo->id + 1);
			// sem_post(philo->data->printing);
			exit(0);
			// sem_post(philo->data->death);
		
			
		
		
		}
	
	
	}
		// printf(" (philo->lastt_lunch) = %llu,(philo->data->t_todie) =%llu ",philo->lastt_lunch,  philo->data->t_todie);
		// exit(0);

	exit(0);
}

void eating(t_philo *philo, int i)
{	
	pthread_t	death;
	philo->id = i;
	// printf("philo->id = %d \n\n", philo->id);
	pthread_create(&death, NULL, &thread_monitoring, philo);
	if (philo->id %2 == 1)
		usleep(1000);
	while(1)
	{
	print_msg("is thinking", philo);
	sem_wait(philo->data->forks);
	print_msg("has taken a fork", philo);
	sem_wait(philo->data->forks);
	print_msg("has taken a fork", philo);
	print_msg("is eating", philo);
	philo_sleeping(philo->data->t_toeat, philo);
	sem_wait(philo->data->death);
	philo->lastt_lunch = get_time();
	sem_post(philo->data->death);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	print_msg("is sleeping", philo);
	philo_sleeping(philo->data->t_tosleep, philo);
	
	}
	pthread_join(philo->monitor, NULL);
	
}



// int main(int ac, char **av)
// {
// 	t_data *data;
// 	t_philo *philo;
	
// 	data = init_data(ac, av);

// 	philo = init_philo(data);
//     pid_t pid[data->n_philos];
//     int     i;
//     int     j;
//     int     status;
//     i = 0;
//     j = 0;
//     while(i < nprocesses)
//     {
//          philo[i].process = fork();
     
//          if (philo[i].process == 0)
//         {
//             //Child stuff here
			
//           eating(&philo[i], i);
		  
		
		  
//         }
//         i++;
// 		// usleep(100);
//     }
	
//     exit_philo(&philo);
	

      
 

// }
void	exit_philo(t_philo **philo)
{
	t_philo	*ptr;
	int		i;
	// int		status;

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
	// sem_unlink("/printing");
	// sem_unlink("/forks");
	
	
	
}
// int creation_processes(t_data *data, t_philo *philo)
// {

// 	(void)data;
//    forker(philo, data->n_philos);
// 	return(0) ;
  
// }