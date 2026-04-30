/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:13:19 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:13:21 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	start_simulation(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->stop_lock);
	table->start_time = get_time_ms();
	i = 0;
	while (i < table->data.number_of_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_eat_lock);
		table->philos[i].last_eat_time = table->start_time;
		pthread_mutex_unlock(&table->philos[i].last_eat_lock);
		i++;
	}
	pthread_mutex_unlock(&table->stop_lock);
}

static void	join_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.number_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

int	simulate(t_table *table)
{
	if (create_philos(table) != 0)
		return (1);
	start_simulation(table);
	monitor_routine(table);
	join_philos(table);
	return (0);
}
