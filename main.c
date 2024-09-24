#include "midorank.h"

static void print_usage(const char *program_name) {
    printf("Usage: ./%s [-t | -n] <file>\n", program_name);
    exit(1);
}

void hash_list(t_midorank *mido, t_page *head) {
    t_links *link;
    size_t hashed_val;

    mido->hash = calloc(mido->page_nb + 1, sizeof(*mido->hash));
    if (!mido->hash) {
        printf("Error: malloc failed\n");
        return;
    }

    for ( ; head; head = head->next) {
        for (link = head->links; link; link = link->next) {
            hashed_val = hash_string(link->link) % mido->page_nb;
            ++mido->hash[hashed_val];
        }
    }
}

size_t page_links(t_page *head, char *haystack) {
    t_links *link;
    size_t link_nb = 0;

    for ( ; head; head = head->next) {
        for (link = head->links; link; link = link->next) {
            if (strcmp(link->link, haystack) == 0) {
                ++link_nb;
            }
        }
    }
    return link_nb;
}

t_page *find_page(t_page *head, const char *name) {
    if (!name)
        return NULL;

    for ( ; head; head = head->next) {
        if (head->name && strcmp(head->name, name) == 0) {
            return head;
        }
    }
    return NULL;
}

size_t get_link_nb(t_links *link) {
    size_t i = 0;

    for ( ; link; link = link->next)
        ++i;
    return i - 1;
}

void init_ranks(t_midorank *mido) {
    t_page *page = mido->page;
    t_links *link, *self_link;

    for ( ; page; page = page->next) {
        if (page == get_superlink(NULL))
            continue;

        page->rank = 1. / mido->page_nb;
        page->prev_rank = page->rank;
        page->link_nb = get_link_nb(page->links);
        ++page->link_nb;

        for (link = page->links; link; link = link->next) {
            link->page = find_page(mido->page, link->link);
        }

        self_link = create_link(page->name);
        self_link->page = page;
        add_link(&page->links, self_link);
    }
    get_superlink(NULL)->rank = 0;
}

void test_midorank(t_midorank *mido) {
    double x = 0;
    for (t_page *page = mido->page; page; page = page->next) {
        if (page == get_superlink(NULL))
            continue;
        x += page->rank;
    }
    printf("%f\n", x);
}

int main(int ac, char **av) {
    t_midorank mido;
    char *opt;

    if (ac < 3)
        print_usage(av[0]);

    opt = av[1];
    if (strcmp("-t", opt) != 0 && strcmp("-n", opt) != 0)
        print_usage(av[0]);

    bzero(&mido, sizeof(t_midorank));

    mido.file = fopen(av[2], "r");
    if (!mido.file) {
        printf("Error: cannot open %s\n", av[2]);
        return 1;
    }

    mido.x = atoi(av[3]);
    mido.k = K_PARAM;

    parse_file(&mido);
    init_ranks(&mido);
    midorank(&mido);
    test_midorank(&mido);
    free_all(&mido);

    return 0;
}
