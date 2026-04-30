#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static int	check_death(t_table *table, int i)
{
	long	time_since_eat;
	int		is_dead;

	is_dead = 0;
	pthread_mutex_lock(&table->philos[i].last_eat_lock);
	time_since_eat = get_time_ms() - table->philos[i].last_eat_time;
	if (time_since_eat >= table->data.time_to_die)
		is_dead = 1;
	pthread_mutex_unlock(&table->philos[i].last_eat_lock);
	return (is_dead);
}

static void	broadcast_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->write_lock);
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag == 0)
	{
		table->stop_flag = 1;
		printf("%ld %d died\n", get_time_ms() - table->start_time,
			table->philos[i].id);
	}
	pthread_mutex_unlock(&table->stop_lock);
	pthread_mutex_unlock(&table->write_lock);
}

static int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->data.must_eat_count == -1)
		return (0);
	i = -1;
	all_ate = 1;
	while (++i < table->data.number_of_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_eat_lock);
		if (table->philos[i].eat_count < table->data.must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&table->philos[i].last_eat_lock);
	}
	return (all_ate);
}

void	monitor_routine(t_table *table)
{
	int	i;

	while (!check_stop(table))
	{
		i = -1;
		while (++i < table->data.number_of_philos)
		{
			if (check_death(table, i))
			{
				broadcast_death(table, i);
				return ;
			}
		}
		if (check_all_ate(table))
		{
			pthread_mutex_lock(&table->stop_lock);
			table->stop_flag = 1;
			pthread_mutex_unlock(&table->stop_lock);
			return ;
		}
		usleep(1000);
	}
}
