#include "philo.h"

static int	error_and_exit(char *str)
{
	ft_putstr_fd(2, str);
	return (1);
}

static int	is_valid(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atoll(char *str)
{
	int		i;
	long	result;

	if (!str || !str[0])
		return (0);
	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (2147483648);
		i++;
	}
	return (result);
}

static void	init_data(t_table *table, int ac, char **av)
{
	table->data.number_of_philos = (int)ft_atoll(av[1]);
	table->data.time_to_die = ft_atoll(av[2]);
	table->data.time_to_eat = ft_atoll(av[3]);
	table->data.time_to_sleep = ft_atoll(av[4]);
	table->data.must_eat_count = -1;
	if (ac == 6)
		table->data.must_eat_count = (int)ft_atoll(av[5]);
}

int	parse(t_table *table, int ac, char **av)
{
	int		i;
	long	value;

	i = 1;
	while (i < ac)
	{
		value = ft_atoll(av[i]);
		if (!is_valid(av[i]))
			return (error_and_exit("Error: value is not numeric!\n"));
		if (value > 2147483647)
			return (error_and_exit("Error: value is very large!\n"));
		if (i == 1 && value <= 0)
			return (error_and_exit("Error: at least one philosopher!\n"));
		if (i > 1 && i < 5 && value <= 0)
			return (error_and_exit("Error: times must be greater than 0!\n"));
		i++;
	}
	init_data(table, ac, av);
	return (0);
}
