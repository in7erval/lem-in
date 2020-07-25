#include "lem-in.h"

void	ft_map_clean(t_map **head)
{
	t_map	*current;

	if (head && *head)
	{
		while (*head)
		{
			current = *head;
			*head = current->next;
			free(current->str);
			free(current);
		}
	}
}

void	ft_map_show(t_map *head)
{
	t_map	*current;

	current = head;
	while (current)
	{
		ft_printf("%s\n", current->str);
		current = current->next;
	}
}

static t_map   *ft_map_create(char *str)
{
    t_map   *current;

    current = malloc(sizeof(t_map));
    if (current)
    {
        current->str = str;
        current->next = NULL;
    }
    return (current);
}

void	ft_map_add(t_map **head, char *str)
{
    t_map   *current;

    if (!(*head))
    {
        *head = ft_map_create(str);
        current = *head;
    }
    else
    {
        current = *head;
        while (current->next)
			current = current->next;
		current->next = ft_map_create(str);
		current = current->next;
    }
}
