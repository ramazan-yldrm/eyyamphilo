/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:13:25 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:13:32 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fail_threads(t_table *table, int created_count)
{
	ft_putstr_fd(2, "Error: Thread creation failed!\n");
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = 1;
	table->start_time = 1;
	pthread_mutex_unlock(&table->stop_lock);
	while (--created_count >= 0)
		pthread_join(table->philos[created_count].thread, NULL);
	return (1);
}

int	create_philos(t_table *table)
{
	int	i;

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
