#include "philo.h"
#include <unistd.h>

int check_stop(t_table *table)
{
	int flag;

	pthread_mutex_lock(&table->stop_lock);
	flag = table->stop_flag;
	pthread_mutex_unlock(&table->stop_lock);
	return (flag);
}

void    wait_for_start(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->write_lock);
		if (table->start_time != 0)
		{
			pthread_mutex_unlock(&table->write_lock);
			break ;
		}
		pthread_mutex_unlock(&table->write_lock);
		usleep(50);
	}
}

static int  fail_threads(t_table *table, int created_count)
{
	ft_putstr_fd(2, "Error: Thread creation failed!\n");
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = 1;
	pthread_mutex_unlock(&table->stop_lock);
	pthread_mutex_lock(&table->write_lock);
	table->start_time = 1;
	pthread_mutex_unlock(&table->write_lock);
	while (--created_count >= 0)
		pthread_join(table->philos[created_count].thread, NULL);
	return (1);
}

static int  create_philo_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->data.number_of_philos)
    {
        if (pthread_create(&table->philos[i].thread, NULL,
                &philo_routine, &table->philos[i]) != 0)
            return (fail_threads(table, i));
        i++;
    }
    return (0);
}

int simulate(t_table *table)
{
    int i;

    if (create_philo_threads(table) != 0)
        return (1);
    pthread_mutex_lock(&table->write_lock);
    table->start_time = get_time_ms();
    i = 0;
    while (i < table->data.number_of_philos)
    {
        pthread_mutex_lock(&table->philos[i].last_eat_lock);
        table->philos[i].last_eat_time = table->start_time;
        pthread_mutex_unlock(&table->philos[i].last_eat_lock);
		i++;
	}
    pthread_mutex_unlock(&table->write_lock);
    monitor_routine(table);
    i = 0;
    while (++i < table->data.number_of_philos)
    {
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
    return (0);
}
