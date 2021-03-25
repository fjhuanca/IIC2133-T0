#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

Person* person_init(int id, int state){
    Person* p = (Person*) malloc(sizeof(Person));
    p->id = id;
    p->state = state;
    p->head = NULL;
    p->next = NULL;
    p->parent = NULL;
    p->prev = NULL;
    p->tail = NULL;
    return p;
    
}

Person* person_append_contact(Person* person, int other_id, int state){
    Person* new;
    new = person_init(other_id, state);
    new->parent = person;
    
    if (person->head == NULL){
        person->head = new;
    }
    else{
        new->prev = person->tail;
        person->tail->next = new;
    }
    person->tail = new;
    return new;
};

Person* person_search_contact(Person* person, int id){
    Person* current = person->head;
    while (current != NULL){
        if (current->id == id) return current;
        current = current->next;
    }
    return NULL;
}

void person_recursive_inform(Person* person, int depth, FILE* file){
    char spc_str[4*depth + 1];
    for (int i=0; i<4*depth; i++){
        spc_str[i] = ' ';
    }
    spc_str[4*depth] = '\0';
    fprintf(file, "%s%d:%d\n",spc_str, person->id, person->state);
    Person* current = person->head;
    while (current != NULL){
        person_recursive_inform(current, depth+1, file);
        current = current->next;
    } 
}
void person_recursive_destroy(Person* person, int depth){
    Person* current = person->head;
    Person* last = NULL;
    while (current != NULL){
        free(last);
        person_recursive_destroy(current, depth+1);
        last = current;  
        current = current->next;  
    }
    free(last);
}