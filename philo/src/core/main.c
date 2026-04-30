#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: enter 5 or 6 arguments\n");
		return (1);
	}
	table.forks = NULL;
	table.philos = NULL;
	if (parse(&table, ac, av))
		return (1);
	if (init(&table))
	{
		clean_table(&table);
		return (1);
	}
	if (simulate(&table))
	{
		clean_table(&table);
		return (1);
	}
	clean_table(&table);
	return (0);
}
