/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:13:14 by ryildiri          #+#    #+#             */
/*   Updated: 2026/05/01 00:13:17 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms, t_table *table)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
	{
		if (check_stop(table))
			break ;
		usleep(500);
	}
}

int	check_stop(t_table *table)
{
	int	flag;

	pthread_mutex_lock(&table->stop_lock);
	flag = table->stop_flag;
	pthread_mutex_unlock(&table->stop_lock);
	return (flag);
}
