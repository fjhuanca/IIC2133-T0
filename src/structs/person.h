#pragma once

#include <stdio.h>

struct person;
typedef struct person Person;

struct person{
    int id;
    int state;
    Person* parent;
    Person* head;
    Person* tail;
    Person* prev;
    Person* next;
};

Person* person_init(int id, int state);
Person* person_append_contact(Person* person, int other_id, int state);
Person* person_search_contact(Person* person, int id);
void person_recursive_inform(Person* person, int depth, FILE* file);