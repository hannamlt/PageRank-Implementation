#include "midorank.h"

static char *split_word(char **line)
{
    const char  *p = strchr(*line, '|');
    char        *new = NULL;

    if (p)
    {
        new = strndup(*line, (size_t)p - (size_t)*line);
        *line += (size_t)p - (size_t)*line + 1;
    }
    else
    {
        new = strdup(*line);
        *line += strlen(*line);
    }
    return new;
}

void parse_file(t_midorank *mido)
{
    char    *line = NULL;
    ssize_t line_read = 0;
    char    *tmp_link;
    char    *ptr;
    char    *page_name = NULL;
    size_t  len = 0;
    t_page  *new_page = NULL;

    while ((line_read = getline(&line, &len, mido->file)) > 0)
    {
        ptr = line;

        if (line[line_read - 1] == '\n')
            line[line_read - 1] = '\0';

        page_name = split_word(&line);
        new_page = create_page(page_name);

        while ((tmp_link = split_word(&line)) && *tmp_link)
        {
            add_link(&new_page->links, create_link(tmp_link));
        }

        add_link(&new_page->links, create_link(SUPER_LINK_NAME));

        if (!*tmp_link)
            free(tmp_link);

        add_page(&mido->page, new_page);
        line = ptr;
        ++mido->page_nb;
    }
    free(ptr);

    new_page = create_page(SUPER_LINK_NAME);
    add_page(&mido->page, new_page);
    get_superlink(new_page);
}
