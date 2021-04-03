#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../structs/person.h"
#include "../structs/world.h"



/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2){
    return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv){
    if (argc != 3){
        printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
        printf("Donde:\n");
        printf("\tINPUT es la ruta del archivo de input\n");
        printf("\tOUTPUT es la ruta del archivo de output\n");
        return false;
    }
    return true;
}

int main(int argc, char **argv){
/* Si los parámetros del programa son inválidos */
    if (!check_arguments(argc, argv)){
    /* Salimos del programa indicando que no terminó correctamente */
        return 1;
    }    

    /* Abrimos el archivo de input */
    FILE *input_file = fopen(argv[1], "r");

    /* Abrimos el archivo de output */
    FILE *output_file = fopen(argv[2], "w");

    char command[32];
  
    /* Leemos la cantidad de países */
    int n_countries;
    fscanf(input_file, "%d", &n_countries);

    /* [Por implementar] Generamos nuestro mundo */
    World* world = world_init(n_countries);

    /* Leemos la cantidad de regiones de cada país */
    int n_regions;
    for (int cty = 0; cty < n_countries; cty++){
        fscanf(input_file, "%d", &n_regions);
    
        /* [Por implementar] Poblamos el país con regiones */
        world_create_region(world, cty, n_regions);
    }

    /* Número de eventos/líneas */
    int n_lines;
    fscanf(input_file, "%d", &n_lines);

    /* Declaramos variables para guardar: 
        - Id de país.
        - Id de región. 
        - Profundidad.
        - Id de contacto para las rutas
        - Número de contactos.
    */
    int country_id;
    int region_id;
    int depth;
    int contact_id;
    int n_contacts;


    while (n_lines){
        /* Disminuimos en 1 el número de líneas por leer */
        n_lines--;

        /* Leemos la instrucción */
        fscanf(input_file, "%s", command);

        /* Obtenemos país, región, y profundidad */
        fscanf(input_file, "%d", &country_id);
        fscanf(input_file, "%d", &region_id);
        

        /* POSITIVE */
        if (string_equals(command, "ADD_CONTACTS")){
            fscanf(input_file, "%d", &depth);
            int route[depth];
            // printf("ADD_CONTACTS %d %d %d ", country_id, region_id, depth);

            /* Obtenemos la ruta desde el archivo*/
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                // printf("%d ", contact_id);
                route[r] = contact_id;
            }
            /* Obtenemos el numero de contactos */
            fscanf(input_file, "%d", &n_contacts);
            // printf("%d\n", n_contacts);
            world_add_contacts(world, country_id, region_id, depth, route, n_contacts);

        } 

        else if (string_equals(command, "POSITIVE")){

            fscanf(input_file, "%d", &depth);
            // printf("POSITIVE %d %d %d ", country_id, region_id, depth);
            /* Obtenemos la ruta desde el archivo*/
            int route[depth];
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                route[r] = contact_id;
                // printf("%d ", contact_id);
            }
            // printf("\n");
            Person* person = world_search(world, country_id, region_id, depth, route);
            person->state = 2;
            Person* prox = person->head;
            while (prox){
                prox->state = 1;
                prox = prox->next;
            }

        } 
        else if (string_equals(command, "NEGATIVE")){
        
            fscanf(input_file, "%d", &depth);
            // printf("NEGATIVE %d %d %d ", country_id, region_id, depth);
            /* Obtenemos la ruta desde el archivo*/
            int route[depth];
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                route[r] = contact_id;
                // printf("%d ", contact_id);
            }
            Person* person = world_search(world, country_id, region_id, depth, route);
            person_discard(person);
            // printf("\n");

        } 
        else if (string_equals(command, "RECOVERED")){
        
            fscanf(input_file, "%d", &depth);
            // printf("RECOVERED %d %d %d ", country_id, region_id, depth);
            /* Obtenemos la ruta desde el archivo*/
            int route[depth];
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                route[r] = contact_id;
                // printf("%d ", contact_id);
            }
            // printf("\n");
            
            /* [Por implementar] */
            Person* person = world_search(world, country_id, region_id, depth, route);
            person->state = 3;

        } 
        else if (string_equals(command, "CORRECT")){
            fscanf(input_file, "%d", &depth);
            // printf("RECOVERED %d %d %d ", country_id, region_id, depth);
            /* Obtenemos la primera ruta desde el archivo*/
            int route1[depth];
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                route1[r] = contact_id;
                // printf("%d ", contact_id);
            }
            Person* person1 = world_search(world, country_id, region_id, depth, route1);


            /* Obtenemos la segunda ruta desde el archivo*/
            fscanf(input_file, "%d", &depth);
            // printf("%d ", depth);
            int route2[depth];
            for (int r = 0; r < depth; r++){
                fscanf(input_file, "%d", &contact_id);
                route2[r] = contact_id;
                // printf("%d ", contact_id);
            }
            // printf("\n");

            Person* person2 = world_search(world, country_id, region_id, depth, route2);

            /* [Por implementar] */
            
            Person* temp_head_1 = person1->head;
            Person* temp_head_2 = person2->head;
            Person* temp_tail_1 = person1->tail;
            Person* temp_tail_2 = person2->tail;
            person1->head = temp_head_2;
            person2->head = temp_head_1;
            person1->tail = temp_tail_2;
            person2->tail = temp_tail_1;
             
            Person* next1 = person1->head;
            Person* next2 = person2->head;
            while (next1){
                if (person1->state == 2){
                    if (next1->state != 2){                        
                        next1->state = 1;
                    }
                }
                next1->parent = person1;
                next1 = next1->next;
            
            }
            while (next2){
                if (person2->state == 2){
                    if (next2->state != 2){                        
                        next2->state = 1;
                    }
                }
                next2->parent = person1;
                next2 = next2->next;
            
            }
        }
        else if (string_equals(command, "INFORM")){
            fprintf(output_file, "INFORM %d %d\n", country_id, region_id);
            /* [Por implementar] */
            world_inform(world, country_id, region_id, output_file);
        } 

        else if (string_equals(command, "STATISTICS")){
            fprintf(output_file, "STATISTICS %d %d\n", country_id, region_id);
            /* [Por implementar] */
            world_statistics(world, country_id, region_id, output_file);
        }

    }

    /*  [Por implementar] Liberamos nuestra estructura */
    world_destroy(world);

    fclose(input_file);
    fclose(output_file);
    return 0;
}