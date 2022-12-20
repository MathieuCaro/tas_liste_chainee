#ifndef ALLOC_H
#define ALLOC_H

#include <stdio.h>
#include <time.h>

#include "linked_list.h"

linked_list *espace_libre;

#define SIZE_TAB 128
#define FREE_BLOCK -1
#define INIT_VAL 0
#define FREE 0
#define FILLED 1

char tas[SIZE_TAB];

void init(void);
char *tas_malloc(unsigned int taille);
int tas_free(char *ptr);
void afficher_tas();
void clean();
void write_log();
void read_log();

#endif