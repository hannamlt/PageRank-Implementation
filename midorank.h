#ifndef MIDORANK_H
# define MIDORANK_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

#define SUPER_LINK_NAME   NULL
#define K_PARAM           20

typedef struct s_page    t_page;
typedef struct s_links   t_links;

typedef struct s_links
{
    char            *link;
    t_page          *page;
    struct s_links  *next;
}   t_links;

typedef struct s_page
{
    double          rank;
    double          prev_rank;
    char            *name;
    size_t          link_nb;
    t_links         *links;
    struct s_page   *next;
}   t_page;

typedef struct  s_midorank
{
    FILE    *file;
    size_t  x;
    size_t  k;
    size_t  page_nb;
    size_t  *hash;
    t_page  *page;
}   t_midorank;

void    parse_file(t_midorank *mido);
t_page  *superlink(t_midorank *mido);
void    midorank(t_midorank *mido);
void    free_all(t_midorank *mido);

size_t  hash_string(const char *str);
size_t  find_hash_val(t_midorank *mido, const char *haystack);

/* linked lists functions */
// t_page
t_page  *get_superlink(t_page *superlink);
t_page  *create_page(char *name);
void    add_page(t_page **head, t_page *new);
void    free_pages(t_page **head);

// t_links
t_links *create_link(char *name);
void    add_link(t_links **head, t_links *new);
void    delete_link(t_links **head, t_links *prev, t_links *to_delete);
void    free_links(t_links **head);

#endif
