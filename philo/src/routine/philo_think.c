/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:13:36 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:13:39 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo, t_table *table)
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
