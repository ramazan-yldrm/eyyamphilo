#include "philo.h"

void	clean_table(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->data.number_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	if (table->philos)
	{
		i = 0;
		while (i < table->data.number_of_philos)
		{
			pthread_mutex_destroy(&table->philos[i].last_eat_lock);
			i++;
		}
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->stop_lock);
	gc_free_all(&table->gc);
}
