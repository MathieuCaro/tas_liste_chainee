#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fonctions.h"

void init(void)
{
    espace_libre = new_element(SIZE_TAB, tas);
    tas[0] = SIZE_TAB - 1;
    tas[1] = FREE_BLOCK;
    for (int i = 2; i < 128; i++)
    {
        tas[i] = 0;
    }
}

char *tas_malloc(unsigned int taille)
{
    linked_list *index = list_search(espace_libre, taille);
    if (index == NULL)
    {
        return NULL;
    }
    if (index->size == taille + 1)
    {
        taille++;
    }

    char *temp = NULL;
    if (index->size == taille)
    {
        *((char *)index->ptr) = 0;
        temp = (char *)index->ptr + 1;

        espace_libre = list_remove(espace_libre, index);
    }
    else if (index->size > taille + 1)
    {
        temp = (char *)index->ptr + 1;
        *((char *)index->ptr) = taille;
        *((char *)index->ptr + 1) = INIT_VAL;
        espace_libre->size = (espace_libre->size - taille - 1);
        *((char *)index->ptr + taille + 2) = -1;
        espace_libre->ptr = (char *)index->ptr + taille + 1;
    }

    return temp;
}

int tas_free(char *ptr)
{

    if (espace_libre == NULL || ptr - (char *)espace_libre->ptr <= 0)
    {
        espace_libre = add_index(espace_libre, *(ptr - 1), 0, ptr);
    }
    *(ptr) = -1;
    ptr++;
    while (*(ptr) != '\0')
    {
        *ptr = 0;
        ptr++;
    }
    return 0;
}

void afficher_tas()
{
    int i, j;
    printf("%ld\n", (char *)espace_libre->ptr - tas);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 16; j++)
        {
            printf("%4d", j + 16 * i);
        }
        printf("\n");
        for (j = 0; j < 16; j++)
        {
            printf("%4d", tas[j + 16 * i]);
        }
        printf("\n");
        for (j = 0; j < 16; j++)
        {
            if (isalnum(tas[j + 16 * i]))
            {
                printf("%4c", tas[j + 16 * i]);
            }
            else
            {
                printf("    ");
            }
        }
        printf("\n");
    }
}
