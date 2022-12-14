#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fonctions.h"

void init(void)
{
    espace_libre = new_element(0);
    tas[0] = SIZE_TAB - 1;
    tas[1] = FREE_BLOCK;
    for (int i = 2; i < 128; i++)
    {
        tas[i] = 0;
    }
}

int index_libre(int taille)
{
    linked_list *temp = espace_libre;
    int index;
    while (temp != NULL)
    {
        index = temp->data;
        if (taille <= tas[index])
        {
            return index;
        }
        temp = temp->next;
    }
    return -1;
}

// rajouter si la taille de tas_mallo(taille) est plus petite que l'espace libéré alors prendre la taille de l'espace libéré

char *tas_malloc(unsigned int taille)
{
    int index = index_libre(taille);
    if (index == FREE_BLOCK)
    {
        return NULL;
    }
    int taille_zone_libre = tas[index];
    if (taille_zone_libre == taille + 1)
    {
        taille++;
    }
    if (taille_zone_libre == taille)
    {
        tas[index + 1] = 0;
        // regarder si l'élement suivant est null(si on est sur le dernier dans ce cas libérer la mémoire puis le mettre à null)
        if (espace_libre->next == NULL)
        {
            free(espace_libre);
            espace_libre = NULL;
        }
        else
            espace_libre = espace_libre->next;

        if (espace_libre && espace_libre->previous)
        {
            free(espace_libre->previous);
            espace_libre->previous = NULL;
        }
    }
    if (taille_zone_libre > taille + 1)
    {
        tas[index] = taille;
        tas[index + 1] = INIT_VAL;
        tas[index + taille + 1] = (char)(taille_zone_libre - taille - 1);
        tas[index + taille + 2] = -1;
        espace_libre->data = index + taille + 1;
    }
    libre = index_libre(1);
    if (libre > 127)
    {
        return NULL;
    }
    else
    {
        return &tas[index + 1];
    }
}

int index_ptr_free(char *ptr)
{
    if (ptr - 1 - tas > libre)
    {
        libre = ptr - 1 - tas;
    }
    return libre;
}

int tas_free(char *ptr)
{
    int index = ptr - 1 - tas;
    if (espace_libre == NULL || index < espace_libre->data)
    {
        espace_libre = add_index(espace_libre, index, 0);
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
    printf("%d\n", espace_libre->data);
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