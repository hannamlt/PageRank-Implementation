#include "midorank.h"

t_page *get_superlink(t_page *superlink)
{
    static t_page *super = NULL;

    if (superlink)
        super = superlink;
    return super;
}

t_page *create_page(char *name)
{
    t_page *page;

    page = malloc(sizeof(t_page));
    if (!page)
        return (NULL);
    bzero(page, sizeof(t_page));
    page->name = name;
    page->next = NULL;
    return (page);
}

void add_page(t_page **head, t_page *new)
{
    t_page *tmp;

    if (!head)
        return;
    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void free_pages(t_page **head)
{
    t_page *tmp;

    while (*head)
    {
        free_links(&(*head)->links);
        free((*head)->name);
        tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
    *head = NULL;
}
