#ifndef __AQUARIUM__H__
#define __AQUARIUM__H__

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
struct aquarium *aquarium__load(FILE *f);
void aquarium__save(aquarium *aq);
int aquarium__add_fish(aquarium *aq, fish *f);
int aquarium__del_fish(aquarium *aq, char *name);
int aquarium__add_view(aquarium *aq, view *v);
int aquarium__del_view(aquarium *aq, char *name);
view *aquarium__get_free_view(aquarium *aq);
view *aquarium__get_view(aquarium *aq, char *name);
fish *aquarium__get_fish(aquarium *aq, char *name);
int aquarium_count_fish_in_view(aquarium *aq, view *v);
void aquarium__free(aquarium *aq);

#endif //__AQUARIUM__H__
