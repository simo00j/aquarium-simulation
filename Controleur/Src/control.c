#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "control.h"

#define MAX_CONNEXION 10
#define MAX_AQUARIUM 10

int is_connected[MAX_CONNEXION] = {0};
int connected_skt_ids[MAX_CONNEXION];
int aquarium_ids[MAX_AQUARIUM] = {0};


int find_place(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == 0)
            return i;
    }
    return -1; //a changer
}

int find_id(int id) {
    for (int i = 0; i < MAX_CONNEXION; i++) {
        if (connected_skt_ids[i] == id)
            return i;
    }
    return 0;
}

int find_aquarium(int id) {
    for (int i = 0; i < MAX_AQUARIUM; i++) {
        if (aquarium_ids[i] == id)
            return i;
    }
    return -1;
}

int control__is_connected(int id) {
    int i = find_id(id);
    return is_connected[i];
}

void control__connect(int id) {
    int i = find_place(is_connected, MAX_CONNEXION);
    is_connected[i] = 1;
    connected_skt_ids[i] = id;
}

void control__disconnect(int id) {
    int i = find_id(id);
    is_connected[i] = 0;
    connected_skt_ids[i] = -1;

    int k = find_aquarium(id);
    if (k > -1)
        aquarium_ids[k] = 0;
}

int control__set_aquarium_id(int skt_id) {
    int k = find_aquarium(skt_id);
    if (k != -1)
        return k;

    int i = find_place(aquarium_ids, MAX_AQUARIUM);
    if (i > -1)
        aquarium_ids[i] = skt_id;
    return i; 
}

int control__set_aquarium_id_named(int aquarium_id, int skt_id) {
    int k = find_aquarium(skt_id);
    if (k != -1)
        return k;

    if (aquarium_id < MAX_AQUARIUM 
    && aquarium_ids[aquarium_id] == 0) {
        aquarium_ids[aquarium_id] = skt_id;
        return aquarium_id;
    }
    else {
        int i = find_place(aquarium_ids, MAX_AQUARIUM);
        if (i > -1)
            aquarium_ids[i] = skt_id;
        return i; 
    }
}