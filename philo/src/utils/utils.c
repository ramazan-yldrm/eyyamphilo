#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static int  ft_strlen(char *str)
{
	int i;

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
	struct timeval  tv;

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

