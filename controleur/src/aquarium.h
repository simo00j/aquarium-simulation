#ifndef __AQUARIUM__H__
#define __AQUARIUM__H__

#include "fish.h"
#include <unistd.h>

#define MAX_VIEWS 32

typedef struct view
{
    char name[3];
    position position;
    size size;
} view;

typedef struct aquarium
{
    size size;
    fish **fish;
    int fish_number;
    view *views[MAX_VIEWS];
    int views_number; 
} aquarium;

aquarium* loadDataFromFile(FILE *f);

aquarium* get_aquarium();

int get_aquarium_data();

// Create a new aquarium with an empty lists of fish and views
aquarium* newAquarium(size s);

// Delete the aquatirum
void delAquarium(aquarium *a);

// Update the fishes positions in the aquarium
void update_aquarium(aquarium* a);

// Add new fish to the aquarium
int addFish( char* name, position pos, size s, position (*p)(position), aquarium *a );

// Delete a fish from the aquarium
void delFish(char* name, aquarium *a);

// Display fishes with current position in the aquairum
void getFishes(aquarium *a);

// Display fishes during the screen evolution
void getFishesContinuously(aquarium *a);

// Display fishes during the screen evolution with respecting the waiting time
void ls(aquarium *a);

// Start fish in the aquarium
void startFish(char* name, aquarium *a);

// Add new view to the aquarium
int addView( char name[], position pos, size s, aquarium *a );

// Delete a view from the aquarium
int delView(char name[], aquarium *a);

#endif //__AQUARIUM__H__