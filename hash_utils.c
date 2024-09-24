#include "midorank.h"

// djb2 algorithm
size_t hash_string(const char *str)
{
    size_t  hash = 5381;
    int     c;

    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

size_t find_hash_val(t_midorank *mido, const char *haystack)
{
    return mido->hash[hash_string(haystack) % mido->page_nb];
}
