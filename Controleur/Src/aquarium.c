#include "aquarium.h"

void exitIf(int cond, char *err)
{
    if (cond)
    {
        fprintf(stderr, "Error : %s\n", err);
        exit(EXIT_FAILURE);
    }
}

aquarium *getDataFromFile(char *filepath)
{
    DEBUG_OUT("DEBUG : Start of getDataFromFile\n");
    aquarium *aq = malloc(sizeof(aquarium));
    aq->views_number = 0;
    FILE *f = fopen(filepath, "r");
    if (!f)
    {
        ERROR_OUT("Couldn't open the input file");
    }

    fscanf(f, "%dx%d\n", &(aq->size.width), &(aq->size.height));
    aq->views = malloc(sizeof(view *));
    view *
        fv;
    while (!feof(f))
    {
        fv = malloc(sizeof(*fv));
        fscanf(f, "%s %dx%d+%d+%d", fv->name, &(fv->position.x), &(fv->position.y), &(fv->size.width), &(fv->size.height));
        aq->views[aq->views_number] = malloc(sizeof(view));
        aq->views[aq->views_number] = fv;
        aq->views_number++;
    }

    fclose(f);
    DEBUG_OUT("DEBUG : End of getDataFromFile\n");
    return aq;
}

int main()
{
    aquarium *aq = getDataFromFile("aquarium1.txt");
    (void)aq;
    return 0;
}
