#include "philo.h"

static void	*handle_single(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->right_fork);
	log_status(philo, "has taken a fork");
	ft_usleep(table->data.time_to_die + 10, table);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	log_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	log_status(philo, "has taken a fork");
}

static void	philo_update_eat_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat_time = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->last_eat_lock);
}

static void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_eat(t_philo *philo, t_table *table)
{
	philo_take_forks(philo);
	log_status(philo, "is eating");
	philo_update_eat_state(philo);
	ft_usleep(table->data.time_to_eat, table);
	philo_release_forks(philo);
}

static void	philo_think(t_philo *philo, t_table *table)
{
	long	time_to_think;

	log_status(philo, "is thinking");
	if (table->data.number_of_philos % 2 != 0)
	{
		time_to_think = (table->data.time_to_eat * 2)
			- table->data.time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		ft_usleep(time_to_think / 2, table);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	wait_for_start(p->table);
	if (p->table->data.number_of_philos == 1)
		return (handle_single(p, p->table));
	if (p->id % 2 == 0)
		ft_usleep(p->table->data.time_to_eat / 10, p->table);
	while (!check_stop(p->table))
	{
		philo_eat(p, p->table);
		log_status(p, "is sleeping");
		ft_usleep(p->table->data.time_to_sleep, p->table);
		philo_think(p, p->table);
	}
	return (NULL);
}
