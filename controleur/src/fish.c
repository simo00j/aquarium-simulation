#include "fish.h"

fish *newFish(char* name, position pos ,size s, position (*p)(position)){
  
    fish *f = malloc(sizeof(fish));
    f->name = name;;
    f->position = pos;
    f->size = s;
    f->path_function = p;
    return f;
}
