#include "fish.h"

position randompos(position * m){
    int r = rand()%4;
    return m[r];
}

bool possible_mvt(size aquarium_size, size fish_size, position r){ // parametre de l'aquarium, du poisson, et la distance du déplacement prévu
    
    if(r.x<0 || r.y<fish_size.height || r.x>(aquarium_size.width-fish_size.width) 
    || r.y>aquarium_size.height){
        return false;
    }
    return true;
}


position * mvts(position p, int distance)){
    position * p = malloc(sizeof(position)*4);
    p[0].x += distance;
    p[1].y += distance;
    p[2].x -= distance;
    p[3].y -= distance;
    return p;
}

/*
    cette fonction retourne un tableau de positions éventuelles du poisson dont
    sa position initiale est entrée en argument


*/
void  RandomWaypoint(struct PathWay p){
    position * P = p->T;
    srand(time(0));
    for (int i = 1; i < (MAX_TIME+1); i++)
    {
        int distance = rand()%p->max_distance;//distance que le poisson prévoit 
        position * m = mvts(P[i-1],distance); //tableau des mouvements 
        position r = randompos(m); // on choisit un mvt/direction au hasard 
        while(!possible_mvt(a->size,f->size,r)){  //tant que le mvt n'est pas possible 
            r = randompos(r); // on rechoisit une direction au hasard 
        }
        P[i].x = r.x; // on ajoute la position éventuelle au tableau P
        P[i].y = r.y;
    }
    
/*
    algorithme pour randomway point 
    pour toute seconde s(i)
        poissonpoisson.choisit_mvt()


*/

}
/* Cette fonction alloue un poisson 
*/

struct fish *newFish(char* name, position pos ,size s, path_type type ){
    struct fish *f = malloc(sizeof(struct fish));
    f->name = name;
    f->position = pos;
    f->size = s;
    f->path = initializePathWay(type,position pos, s->width);
    return f;
}

/* cette fonction alloue l'attribut PathWay d'un poisson 
*/

struct PathWay *initializePathWay(path_type t, position pos, int m ){
    Pathway * p = malloc((struct PathWay)*MAX_TIME);
    p->type = t;
    p->max_distance = m;
    p->T=malloc((struct position)*MAX_TIME);
    p->T[0] = pos;
    return p;
}
/*cette fonction free un poisson
*/
void freeFish(struct fish * f){
    free(f->path->T);
    free(f->path);
    free(f);
}

/* cette fonction retourne l'indice du poisson dont le nom est rentré en paramètre
dans l'aquarium ou -1 s'il n'existe pas 
*/

int containsfish(aquarium *a ,char * name ){
    for (int i=0; i<a->fish_number ;i++){
        if (a->fish[i]->name==name)
            return i;
    }
    return -1;
}

/* cette fonction ajoute un poisson à l'aquarium s'il n'y existe déjà
*/

void addFish( char* name, position pos ,size s, PathWay p,aquarium *a ){
    if (containsfish(a,name)!=-1){
        printf("NOK");
    }else{
        struct fish *f = newFish(name,pos,s,p,a);
        a->fish[fish_number] = f;
        a->fish_number++;
        printf("OK");
    }
    return;
}
void startFish(char* name, aquarium *a){
    int l = containsfish(a,name);
    if (l!=-1){
        printf("NOK");
        return;
    }
    fish * f = a->fish[i];
    size fsize = f->size;
    size asize = a->size;
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

void ls(aquarium *a){



}




*/
