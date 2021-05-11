#include <string.h>
#include "aquarium.h"
#include "debug.h"

aquarium *aquarium__empty()
{
    aquarium *aq = malloc(sizeof(aquarium));
    aq->frame = frame__from_str(AQUARIUM__DEFAULT_FRAME);
    STAILQ_INIT(&(aq->fish_list));
    STAILQ_INIT(&(aq->views_list));

    ////// TMP ///////
    view *v = malloc(sizeof(view));
    v->frame = frame__from_str(AQUARIUM__DEFAULT_FRAME);
    v->name = malloc(sizeof(char) * VIEW_NAME_MAX_SIZE);
    sscanf("NPA", "%s", v->name);
    STAILQ_INSERT_HEAD(&(aq->views_list), v, next);

    return aq;
}

void aquarium__load(aquarium *aq, FILE *f)
{
    DEBUG_OUT("entering aquarium__load\n");
    char line[256];
    view *v;
    aq->frame = malloc(sizeof(frame));
    STAILQ_INIT(&(aq->fish_list));
    STAILQ_INIT(&(aq->views_list));
    fgets(line, sizeof(line), f);
    sscanf(line, "%dx%d", &(aq->frame->width), &(aq->frame->height));

    while (fgets(line, sizeof(line), f))
    {
        v = malloc(sizeof(view));
        v->frame = malloc(sizeof(frame));
        v->name = malloc(sizeof(char) * VIEW_NAME_MAX_SIZE);
        sscanf(line, "%s %dx%d+%d+%d", v->name, &(v->frame->x), &(v->frame->y), &(v->frame->width), &(v->frame->height));
        STAILQ_INSERT_HEAD(&(aq->views_list), v, next);
    }
    DEBUG_OUT("quitting aquarium__load\n");
}

void aquarium__save(const aquarium *aq, const char *filename)
{
    DEBUG_OUT("entering aquarium__save\n");
    FILE *f = fopen(filename, "w");
    fprintf(f, "%dx%d\n", aq->frame->width, aq->frame->height);

    view *v;
    STAILQ_FOREACH(v, &(aq->views_list), next)
    {
        fprintf(f, "%s %dx%d+%d+%d\n", v->name, v->frame->x, v->frame->y, v->frame->width, v->frame->height);
    }
    fprintf(f, "\n");
    fclose(f);
    DEBUG_OUT("quitting aquarium__save\n");
}

int aquarium__add_fish(aquarium *aq, fish *f)
{
    DEBUG_OUT("entering aquarium__add_fish\n");
    fish *fish;
    STAILQ_FOREACH(fish, &(aq->fish_list), next)
    {
        DEBUG_OUT("aquarium__add_fish : comparing fish names\n");
        if (strcmp(fish->name, f->name) == 0)
        {

            DEBUG_OUT("quitting aquarium__add_fish without adding %s\n", f->name);
            return -1;
        }
    }
    DEBUG_OUT("aquarium__add_fish : adding fish\n");
    STAILQ_INSERT_HEAD(&(aq->fish_list), f, next);
    DEBUG_OUT("quitting aquarium__add_fish after adding %s\n", f->name);
    return 0;
}

int aquarium__del_fish(aquarium *aq, const char *name)
{
    fish *f;
    STAILQ_FOREACH(f, &(aq->fish_list), next)
    {
        if (strcmp(f->name, name) == 0)
        {
            STAILQ_REMOVE(&(aq->fish_list), f, fish, next);
            return 0;
        }
    }
    return -1;
}

int aquarium__add_view(aquarium *aq, view *v)
{
    view *view;
    DEBUG_OUT(" enteringaquarium__add_view");
    STAILQ_FOREACH(view, &(aq->views_list), next)
    {
        if (!strcmp(view->name, v->name))
        {
            return -1;
        }
    }
    STAILQ_INSERT_TAIL(&(aq->views_list), v, next);
    return 0;
}

int aquarium__del_view(aquarium *aq, const char *name)
{
    view *v;
    STAILQ_FOREACH(v, &(aq->views_list), next)
    {
        if (!strcmp(v->name, name))
        {
            STAILQ_REMOVE(&(aq->views_list), v, view, next);
            view__free(v);
            return 0;
        }
    }
    return -1;
}

view *aquarium__get_free_view(const aquarium *aq)
{
    view *v;
    STAILQ_FOREACH(v, &(aq->views_list), next)
    {
        if (v->taken == 0)
        {
            return v;
        }
    }
    return NULL;
}

view *aquarium__get_view(const aquarium *aq, const char *name)
{
    view *v;
    STAILQ_FOREACH(v, &(aq->views_list), next)
    {
        if (strcmp(v->name, name) == 0)
        {
            return v;
        }
    }
    return NULL;
}

fish *aquarium__get_fish(const aquarium *aq, const char *name)
{
    fish *f;
    STAILQ_FOREACH(f, &(aq->fish_list), next)
    {
        if (!strcmp(f->name, name))
        {
            return f;
        }
    }
    return NULL;
}

int aquarium__count_fish_in_view(const aquarium *aq, const view *v)
{
    fish *f;
    int i = 0;
    STAILQ_FOREACH(f, &(aq->fish_list), next)
    {
        if (frame__includes_snippet(v->frame, f->frame))
        {
            i++;
        }
    }
    return i;
}

int aquarium__count_views(const aquarium *aq)
{
    view *v;
    int i = 0;
    STAILQ_FOREACH(v, &(aq->views_list), next)
    {
        i++;
    }
    return i ;
}

void aquarium__free(aquarium *aquarium)
{
    view *v;
    fish *f;
    while (!STAILQ_EMPTY(&(aquarium->views_list)))
    {
        v = STAILQ_FIRST(&(aquarium->views_list));
        STAILQ_REMOVE_HEAD(&(aquarium->views_list), next);
        view__free(v);
    }
    while (!STAILQ_EMPTY(&(aquarium->fish_list)))
    {
        f = STAILQ_FIRST(&(aquarium->fish_list));
        STAILQ_REMOVE_HEAD(&(aquarium->fish_list), next);
        fish__free(f);
    }
    free(aquarium->frame);
    free(aquarium);
}
