#include "fish.h"




struct fish *newFish(char* name, position pos ,size s, pathWay p){
    struct fish *f = malloc(sizeof(struct fish));
    f->name = name;
    f->position = pos;
    f->size = s;
    f->path_function = p;
    return f;
}

int containsfish(aquarium *a ,char * name ){
    for (int i=0; i<a->fish_number ;i++){
        if (a->fish[i]->name==name)
            return i;
    }
    return -1;
}

void addFish( char* name, position pos ,size s, pathWay p,aquarium *a ){
    if (containsfish(a,name)!=-1){
        printf("NOK");
    }else{
       struct fish *f = newFish(name,pos,s,p);
        a->fish[fish_number] = f;
        a->fish_number++;
        printf("OK");
    }
    return;
}
void startFish(char* name, aquarium *a){
   
    printf("OK");
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
/*
void getFishes(aquarium *a){

    printf("list ")
    for (int i = 0; i < a->fish_number; i++)
    {
        struct fish *f = a->fish[i];
        printf("[ %s at %dx%d, %dx%d,%d]",f->name,f->pos->x,f->pos->y,f->size->width,size->height,);
    }
    
}

void getFishesContinuously(aquarium *a){

}
*/