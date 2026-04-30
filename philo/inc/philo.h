#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_table	t_table;

typedef struct s_data
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_philos;
	int		must_eat_count;	
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				eat_count;
	long			last_eat_time;
	pthread_mutex_t	last_eat_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			start_time;
	int				stop_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_lock;
	t_data			data;
	t_philo			*philos;
	t_gc			*gc;
}	t_table;

int		parse(t_table *table, int ac, char **av);
int		init(t_table *table);
int		simulate(t_table *table);

int		check_stop(t_table *table);
void	wait_for_start(t_table *table);
void	*philo_routine(void *arg);
void	monitor_routine(t_table *table);

void	*gc_malloc(t_gc **list, size_t size);
void	gc_free_all(t_gc **list);
void	clean_table(t_table *table);
void	ft_putstr_fd(int fd, char *str);
long	get_time_ms(void);
void	ft_usleep(long ms, t_table *table);
void	log_status(t_philo *philo, char *status);

#endif
