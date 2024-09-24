#include "midorank.h"

void midorank(t_midorank *mido)
{
    t_links *link;
    t_page  *page;
    bool    first;

    while (mido->k-- > 0)
    {
        page = mido->page;
        for ( ; page; page = page->next)
        {
            if (page == get_superlink(NULL))
                continue;

            double y = 0.0;
            for (link = page->links; link; link = link->next)
            {
                if (link->page == get_superlink(NULL))
                    continue;
                y += link->page->prev_rank;
            }

            first = true;
            for (link = page->links; link; link = link->next)
            {
                if (page == get_superlink(NULL))
                    continue;
                if (first)
                {
                    page->rank = link->page->prev_rank * (1. - 1. / (10. * mido->page_nb)) / link->page->link_nb;
                    first = false;
                }
                else
                    page->rank += link->page->prev_rank * (1. - 1. / (10. * mido->page_nb)) / link->page->link_nb;
            }
            page->rank += (1. / mido->page_nb) * get_superlink(NULL)->rank;
        }

        first = true;
        for (page = mido->page; page; page = page->next)
        {
            if (page == get_superlink(NULL))
                continue;
            page->prev_rank = page->rank;
            if (first)
            {
                get_superlink(NULL)->rank = page->rank * (1. / (10. * mido->page_nb));
                first = false;
            }
            else
            {
                get_superlink(NULL)->rank += page->rank * (1. / (10. * mido->page_nb));
            }
        }
    }
}
