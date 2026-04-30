/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:13:41 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:13:44 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	wait_for_start(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->stop_lock);
		if (table->start_time != 0 || table->stop_flag)
		{
			pthread_mutex_unlock(&table->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&table->stop_lock);
		usleep(100);
	}
}

static void	*handle_single(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->right_fork);
	log_status(philo, "has taken a fork");
	ft_usleep(table->data.time_to_die + 10, table);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
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
