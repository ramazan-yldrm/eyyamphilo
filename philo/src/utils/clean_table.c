#include "philo.h"
#include <stdlib.h>

void    clean_table(t_table *table)
{
	int     i;

	if (table->forks)
	{
		i = 0;
		while (i < table->data.number_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (table->philos)
	{
		i = 0;
		while (i < table->data.number_of_philos)
		{
			pthread_mutex_destroy(&table->philos[i].last_eat_lock);
			i++;
		}
		free(table->philos);
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->stop_lock);
}
