#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static long	get_last_eat_time(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_eat = philo->last_eat_time;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (last_eat);
}

static long	check_death(t_table *table, int i)
{
	long	last_eat;

	last_eat = get_last_eat_time(&table->philos[i]);
	if ((get_time_ms() - last_eat) >= table->data.time_to_die)
		return (last_eat + table->data.time_to_die);
	return (0);
}

static void	broadcast_death(t_table *table, int i, long death_time)
{
	pthread_mutex_lock(&table->write_lock);
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag == 0)
	{
		table->stop_flag = 1;
		printf("%ld %d died\n", death_time - table->start_time,
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

static void	set_stop_flag(t_table *table)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = 1;
	pthread_mutex_unlock(&table->stop_lock);
}

void	monitor_routine(t_table *table)
{
	int		i;
	long	death_time;

	while (!check_stop(table))
	{
		i = -1;
		while (++i < table->data.number_of_philos)
		{
			death_time = check_death(table, i);
			if (death_time)
			{
				broadcast_death(table, i, death_time);
				return ;
			}
		}
		if (check_all_ate(table))
		{
			set_stop_flag(table);
			return ;
		}
		usleep(1000);
	}
}
