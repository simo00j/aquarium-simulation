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
void aquarium__save(const aquarium *aq, const char *filename);
int aquarium__add_fish(aquarium *aq, fish *f);
int aquarium__del_fish(aquarium *aq, const char *name);
int aquarium__add_view(aquarium *aq, view *v);
int aquarium__del_view(aquarium *aq, const char *name);
int aquarium__count_views(const aquarium *aq);
view *aquarium__get_free_view(const aquarium *aq);
view *aquarium__get_view(const aquarium *aq, const char *name);
fish *aquarium__get_fish(const aquarium *aq, const char *name);
int aquarium__count_fish_in_view(const aquarium *aq, const view *v);
void aquarium__free(aquarium *aq);

#endif //AQUARIUM_H
