#include "../src/aquarium.h"
#include "../src/fish.h"


position add(position p){
    position np;
    np.x = p.x + 1;
    np.y = p.y + 1;

    return np;
}
int main(){

    aquarium* a = malloc(sizeof(aquarium*));
    
    size s;
    s.width = 20;
    s.height = 20;
    a->size = s;
    a->fish_number = 0;
    a->views_number = 0;
    a->fish = malloc(sizeof(fish**));
    
    char *name= "samaka";
    size s2;
    s2.width = 2;
    s2.height = 2;
    position pos;
    pos.x = 10;
    pos.y = 10;

    addFish(name,pos,s2,add,a);
    getFishes(a);
    delFish(name,a);

    free(a->fish);
    free(a);

    return 0;

}
