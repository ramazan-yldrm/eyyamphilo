/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:14:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:14:02 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	clean_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.number_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

static void	clean_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.number_of_philos)
	{
		pthread_mutex_destroy(&table->philos[i].last_eat_lock);
		i++;
	}
	free(table->philos);
}

void	clean_table(t_table *table)
{
	if (table->forks)
		clean_forks(table);
	if (table->philos)
		clean_philos(table);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->stop_lock);
}
