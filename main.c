#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fonctions.h"


int main(){
    init();

    char* p1 = tas_malloc(10);
    char* p2 = tas_malloc(9);
    char* p3 = tas_malloc(5);
    strcpy(p1,"tp 1");
    strcpy(p2,"tp 2");
    strcpy(p3,"tp 3");
    tas_free(p2);
    char* p4 = tas_malloc(8);
    strcpy(p4,"systeme");
    return 0;
}

