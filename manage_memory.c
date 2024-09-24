#include "midorank.h"

void free_all(t_midorank *mido)
{
    fclose(mido->file);
    free_pages(&mido->page);
    free(mido->hash); // Libérer le tableau de hash
}
