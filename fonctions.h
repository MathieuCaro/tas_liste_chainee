#ifndef ALLOC_H
#define ALLOC_H

#define SIZE_TAB 128
//#define SIZE_TAB_INIT_FREE 127
#define FREE_BLOCK -1
#define INIT_VAL 0

typedef struct linked_list
{
    int data;
    struct linked_list *next;
    struct linked_list *previous;

} linked_list;

char tas[SIZE_TAB];
int libre;

linked_list *new_element(int data);

void init(void);
int index_libre(int taille);
char *tas_malloc(unsigned int taille);
int tas_free(char *ptr);
void afficher_tas();
int index_ptr_free(char *ptr);
linked_list *add_index(linked_list *head, int data, int index);
void list_free();

#endif