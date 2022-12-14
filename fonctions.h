#ifndef ALLOC_H
#define ALLOC_H

#include "linked_list.h"

linked_list *espace_libre;

#define SIZE_TAB 128
// #define SIZE_TAB_INIT_FREE 127
#define FREE_BLOCK -1
#define INIT_VAL 0

char tas[SIZE_TAB];
int libre;

void init(void);
int index_libre(int taille);
char *tas_malloc(unsigned int taille);
int tas_free(char *ptr);
void afficher_tas();
int index_ptr_free(char *ptr);

#endif