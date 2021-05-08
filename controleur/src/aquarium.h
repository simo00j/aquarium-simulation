#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "view.h"
#include "frame.h"
#include "fish.h"

#define AQUARIUM__DEFAULT_FRAME "0x0+1000+1000"

typedef struct aquarium
{
    frame *frame;
    STAILQ_HEAD(, fish)
    fish_list;
    STAILQ_HEAD(, view)
    views_list;
} aquarium;

aquarium *aquarium__empty();
void aquarium__load(aquarium *aq, FILE *f);
void aquarium__save(aquarium *aq, char *filename);
int aquarium__add_fish(aquarium *aq, fish *f);
int aquarium__del_fish(aquarium *aq, char *name);
int aquarium__add_view(aquarium *aq, view *v);
int aquarium__del_view(aquarium *aq, char *name);
int aquarium__count_views(aquarium *aq);
view *aquarium__get_free_view(aquarium *aq);
view *aquarium__get_view(aquarium *aq, char *name);
fish *aquarium__get_fish(aquarium *aq, char *name);
int aquarium__count_fish_in_view(aquarium *aq, view *v);
void aquarium__update_fish_randomly(aquarium *aq);
void aquarium__free(aquarium *aq);

#endif //AQUARIUM_H
