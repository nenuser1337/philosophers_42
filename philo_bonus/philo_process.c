#include "philo_bonus.h"


t_data	*init_data(int ac, char **av)
{
	t_data	*data;
	int		i;
	(void)ac;
	(void)av;
	
	i = 0;
	data = malloc(sizeof(t_data));
	data->t_todie = 300;
	data->t_toeat = 200;
	data->t_tosleep =100;
	if (ac == 6)
		data->should_eat = 5;
	else
		data->should_eat = -1;
	data->has_eaten = 0;
	data->n_philos = 4;
	data->dead = 0;
	sem_unlink("/forks");
	sem_unlink("/printing");
	sem_unlink("/death");
	data->forks = sem_open("/forks", O_CREAT, 0600, data->n_philos);
	data->death = sem_open("/death", O_CREAT, 0600, 1);
	data->printing = sem_open("/printing", O_CREAT, 0600, 1);
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
// int	main(int ac, char **av)
// {
// 	t_data *data;
// 	t_philo *philo;
	
// 	data = init_data(ac, av);

// 	philo = init_philo(data);
	
// 	creation_processes(data, philo);
// 	return 0;
// }
int main(int ac, char **av)
{
	t_data *data;
	t_philo *philo;
	
	data = init_data(ac, av);

	philo = init_philo(data);
    pid_t pid[data->n_philos];
    int     i;
    int     j;
    int     status;
    i = 0;
    j = 0;
    while(i < data->n_philos)
    {
         philo[i].process = fork();
     
         if (philo[i].process == 0)
        {
            //Child stuff here
			
          eating(&philo[i], i);
		   }
        i++;
		// usleep(100);
    }
	waitpid(-1, &status, 0);
    exit_philo(&philo);
	

      
	return 0;

}