#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fonctions.h"

int main()
{
    init();

    char *p1 = tas_malloc(10);
    char *p2 = tas_malloc(9);
    char *p3 = tas_malloc(5);
    strcpy(p1, "tp 1");
    strcpy(p2, "tp 2");
    strcpy(p3, "tp 3");
    // tas_free(p2);
    /*char *p4 = tas_malloc(8);
    strcpy(p4, "systeme");
    char *p5 = tas_malloc(10);
    char *p6 = tas_malloc(9);
    char *p7 = tas_malloc(5);
    strcpy(p5, "tp 5");
    strcpy(p6, "tp 6");
    strcpy(p7, "tp 7");
    tas_free(p3);
    tas_free(p6);
    char *p8 = tas_malloc(20);
    strcpy(p8, "azertyyuopqdhkldlff");
    char *p9 = tas_malloc(6);
    strcpy(p9, "azert");
    tas_free(p1);
    tas_free(p4);
    tas_free(p5);
    tas_free(p7);
    tas_free(p8);
    tas_free(p9);*/
    afficher_tas();
    clean();
    return 0;
}
