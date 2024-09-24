#include "midorank.h"

t_links	*create_link(char *name)
{
	t_links	*link;

	link = malloc(sizeof(t_links));
	if (!link)
		return (NULL);
	bzero(link, sizeof(t_links));
	link->link = name;
	return (link);
}

void	add_link(t_links **head, t_links *new)
{
	t_links	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	delete_link(t_links **head, t_links *prev, t_links *to_delete)
{
	if (!prev)
	{
		*head = to_delete->next;
	}
	else
	{
		prev->next = to_delete->next;
	}
	free(to_delete->link);
	free(to_delete);
}

void	free_links(t_links **head)
{
	t_links	*tmp;

	while (*head)
	{
		free((*head)->link);
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}
