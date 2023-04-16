#include "philo_bonus.h"

void	philo_sleeping(unsigned long duree, t_philo *philo)
{
	unsigned long	current;

	current = get_time();
	while (get_time() - current < duree)
	{
	
		usleep(200);
	}

}

void	print_msg(char *str, t_philo *philo)
{
	sem_wait(philo->data->printing);
	printf("%llu %d %s\n", (get_time() - philo->data->t_start), philo->id + 1,
			str);
	sem_post(philo->data->printing);


}