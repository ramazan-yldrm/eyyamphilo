#include "philo.h"

static int	init_forks(t_table *table)
{
	int	i;
	int	n;

	n = table->data.number_of_philos;
	table->forks = gc_malloc(&table->gc, sizeof(pthread_mutex_t) * n);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	fork_turn(t_philo *philo, t_table *table, int i)
{
	int	n;

	n = table->data.number_of_philos;
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &table->forks[i];
		philo->left_fork = &table->forks[(i + 1) % n];
	}
	else
	{
		philo->right_fork = &table->forks[(i + 1) % n];
		philo->left_fork = &table->forks[i];
	}
}

static int	init_philos(t_table *table)
{
	int	i;
	int	n;

	n = table->data.number_of_philos;
	table->philos = gc_malloc(&table->gc, sizeof(t_philo) * n);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < n)
	{
		table->philos[i].id = i + 1;
		fork_turn(&table->philos[i], table, i);
		table->philos[i].eat_count = 0;
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i].last_eat_lock, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init(t_table *table)
{
	table->stop_flag = 0;
	table->start_time = 0;
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (1);
	if (init_forks(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}
