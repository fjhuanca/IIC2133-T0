#pragma once

#include <stdio.h>
#include "person.h"

typedef struct world{
    int n_countries;
    int* n_regions_countries;
    Person*** countries;
    int** people_count;
} World;

World* world_init(int n_countries);
void world_destroy(World* world);
void world_create_region(World* world, int idx, int amount);
Person* world_search(World* world, int country_idx, int region_idx, int depth, int* route);
Person* world_add_contact(World* world, Person* person, int new_id);
void world_add_contacts(World* world, int country_idx, int region_idx, int depth,
                        int* route, int n_contacts);
void world_inform(World* world, int country_idx, int region_idx, FILE* file);

