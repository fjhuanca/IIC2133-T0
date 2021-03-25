#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "world.h"
#include "person.h"

World* world_init(int n_countries){
    World* world = malloc(sizeof(World));

    int* n_regions_countries = calloc(n_countries, sizeof(int));
    Person*** countries = calloc(n_countries, sizeof(Person**));
    int** people_count = calloc(n_countries, sizeof(int*));
    
    world->n_countries = n_countries;
    world->n_regions_countries = n_regions_countries;
    world->countries = countries;
    world->people_count = people_count;
    return world;
}

void world_destroy(World* world){
    for (int i=0; i<world->n_countries; i++){
        for (int j=0; j<world->n_regions_countries[i]; j++){
            Person* first = world->countries[i][j];
            person_recursive_destroy(first, 0);
            free(world->countries[i][j]);
        }
        free(world->countries[i]);
        free(world->people_count[i]);
    }
    free(world->n_regions_countries);
    free(world->countries);
    free(world->people_count);
    free(world);

}

void world_create_region(World* world, int idx, int amount){
    world->n_regions_countries[idx] = amount;
    world->countries[idx] = (Person**) malloc(amount * sizeof(Person*));
    world->people_count[idx] = (int*) malloc (amount * sizeof(int));
    for (int i=0; i<amount; i++){
        world->countries[idx][i] = person_init(0, 2);
        world->people_count[idx][i] = 1;
    }
}

Person* world_search(World* world, int country_idx, int region_idx, int depth, int* route){
    Person* person = world->countries[country_idx][region_idx];
    for (int i=0; i<depth; i++){
        person = person_search_contact(person, route[i]);
    }
    return person;
}

Person* world_add_contact(World* world, Person* person, int new_id){
    int state;
    if (person->state == 2) state = 1;
    else state = 0;
    return person_append_contact(person, new_id, state);
}

void world_add_contacts(World* world, int country_idx, int region_idx, int depth,
                        int* route, int n_contacts){
    
    Person* person;
    person = world_search(world, country_idx, region_idx, depth, route);
    for (int i=0; i<n_contacts; i++){
        int new_id = world->people_count[country_idx][region_idx];
        world_add_contact(world, person, new_id);
        world->people_count[country_idx][region_idx] ++;
    }
}

void world_inform(World* world, int country_idx, int region_idx, FILE* file){
    Person* first = world->countries[country_idx][region_idx];
    person_recursive_inform(first, 0, file); 
}