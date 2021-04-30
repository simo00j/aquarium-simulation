#include "aquarium.h"
#include <string.h>

aquarium* aq = NULL;

void exitIf(int cond, char *err)
{
    if (cond)
    {
        fprintf(stderr, "Error : %s\n", err);
        exit(EXIT_FAILURE);
    }
}

void print_aquarium(aquarium* a){
    if(a != NULL) {
        printf("Size: %d x %d\n\n", a->size.width, a->size.height);
        printf("Views:\n");
        for (int i = 0; i < a->views_number; i++) {
            printf("\t%s %dx%d+%d+%d\n", a->views[i]->name, a->views[i]->position.x, a->views[i]->position.y, a->views[i]->size.width, a->views[i]->size.height);
        }
    }
}

//TODO
int get_aquarium_data(char* buffer) {
    if(aq == NULL) 
        return 0;
    return 1;
}

aquarium* loadDataFromFile(FILE *f)
{
    aq = malloc(sizeof(aquarium));
    aq->views_number = 0;
    fscanf(f, "%dx%d\n", &(aq->size.width), &(aq->size.height));

    while (!feof(f))
    {
        view* fv = malloc(sizeof(fv));
        fscanf(f, "%s %dx%d+%d+%d", fv->name, &(fv->position.x), &(fv->position.y), &(fv->size.width), &(fv->size.height));
        aq->views[aq->views_number] = malloc(sizeof(view));
        aq->views[aq->views_number] = fv;
        aq->views_number++;
    }
    return aq;
}

aquarium* get_aquarium() {
    return aq;
}

aquarium* newAquarium(size s){
    aquarium *a = malloc(sizeof(aquarium*));
    a->size = s;
    a->fish = malloc(sizeof(fish**));
    a->fish_number = 0;
    //a->views = malloc(sizeof(view**));
    a->views_number = 0;

    return a;
}

void delAquarium(aquarium *a){
    free(a->fish);
    free(a->views);
    free(a);
}

int containsfish(aquarium *a ,char * name ){
    for (int i=0; i<a->fish_number ;i++){
        if (a->fish[i]->name==name)
            return i;
    }
    return -1;
}

int addFish( char* name, position pos, size s, position(*p)(position), aquarium *a ){

    if (containsfish(a,name)!=-1){
        //printf("NOK");
        return 0;
    }else{
        fish *f = newFish(name,pos,s,p);
        a->fish[a->fish_number] = f;
        a->fish_number++;
        //printf("OK");
        return 1;
    }
}

void update_aquarium(aquarium* a){
    for (int i = 0; i < a->fish_number; i++)
        a->fish[i]->position = a->fish[i]->path_function(a->fish[i]->position);
}

void getFishes(aquarium *a){

    printf("list ");
    for (int i = 0; i < a->fish_number; i++){
        fish *f = a->fish[i];
        printf("[ %s at %dx%d, %dx%d,%d]",f->name,f->position.x,f->position.y,f->size.width,f->size.height,waiting_time);
    }
    
}

void getFishesContinuously(aquarium *a){

    while(1){
        getFishes(a);
        update_aquarium(a);
    }
}

void ls(aquarium *a){
    while(1){
        getFishes(a);
        update_aquarium(a);
        //sleep(waiting_time);
    }
}

void delFish(char* name, aquarium *a){
    int indice = containsfish(a,name);
    if (indice!=-1){
        free(a->fish[indice]);
        for (int i = indice; i < a->fish_number-1; i++)
        {
            a->fish[i]=a->fish[i+1];
        }
        a->fish_number--;
        printf("OK");
    }else{
        printf("NOK");
    }
    return;
}

void startFish(char* name, aquarium *a){   
    printf("OK");
}

/*int main()
{
    aquarium *aq = getDataFromFile("aquarium1.txt");
    (void)aq;
    return 0;
}*/
