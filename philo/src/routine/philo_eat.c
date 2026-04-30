/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:14:24 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:14:27 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philo_eat(t_philo *philo, t_table *table)
{
	philo_take_forks(philo);
	log_status(philo, "is eating");
	philo_update_eat_state(philo);
	ft_usleep(table->data.time_to_eat, table);
	philo_release_forks(philo);
}
