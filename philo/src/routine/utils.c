/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:14:12 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:14:16 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	log_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_lock(&philo->table->stop_lock);
	if (!philo->table->stop_flag)
	{
		time = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
}
