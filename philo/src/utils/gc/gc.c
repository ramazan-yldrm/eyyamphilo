#include "philo.h"
#include <stdlib.h>

static void	gc_add(t_gc **list, void *ptr)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		free(ptr);
		return ;
	}
	new_node->ptr = ptr;
	new_node->next = *list;
	*list = new_node;
}

void	*gc_malloc(t_gc **list, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd(2, "Error: malloc fail!");
		return (NULL);
	}
	gc_add(list, ptr);
	return (ptr);
}

void	gc_free_all(t_gc **list)
{
	t_gc	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->ptr);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
