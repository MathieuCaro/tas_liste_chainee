#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fonctions.h"

void init(void)
{
    espace_libre = new_element(SIZE_TAB, tas, FREE);
}

linked_list *first_fit(linked_list *head, int size)
{
    linked_list *list_search = head;
    while (list_search)
    {
        if ((list_search->filled == FREE) && (list_search->size >= size))
        {
            return list_search;
        }
        list_search = list_search->next;
    }
    return NULL;
}

char *tas_malloc(unsigned int taille)
{
    linked_list *index = first_fit(espace_libre, taille);
    char *temp = NULL;
    int size_old_elmt;
    if (index == NULL)
    {
        return NULL;
    }
    if (index->size == taille)
    {
        temp = (char *)index->ptr;
        index->filled = FILLED;
    }
    else if (index->size > taille)
    {
        size_old_elmt = index->size;
        index->size = taille;
        index->filled = FILLED;
        linked_list *nouvel_elmt = new_element(size_old_elmt - taille, (char *)index->ptr + taille, FREE);
        add_after(index, nouvel_elmt);

        temp = index->ptr;
    }
    write_log("malloced", index->size, temp);
    return temp;
}

int tas_free(char *ptr)
{
    linked_list *free_ptr = espace_libre;
    while (free_ptr)
    {
        if (free_ptr->ptr == ptr)
        {
            free_ptr->filled = FREE;
            break;
        }
        free_ptr = free_ptr->next;
    }
    if (free_ptr == NULL)
    {
        return 0;
    }
    write_log("freed", free_ptr->size, ptr);
    if ((free_ptr->next) && (free_ptr->next->filled == FREE))
    {
        free_ptr->size += free_ptr->next->size;
        list_remove(espace_libre, free_ptr->next);
    }
    if ((free_ptr->previous) && (free_ptr->previous->filled == FREE))
    {
        free_ptr->previous->size += free_ptr->size;
        list_remove(espace_libre, free_ptr);
    }

    return 0;
}

void afficher_tas()
{
    int i, j;
    if (espace_libre == NULL)
    {
        printf("0\n");
    }
    else
    {
        printf("%ld\n", (char *)espace_libre->ptr - tas);
    }

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

void clean()
{
    list_free(espace_libre);
}