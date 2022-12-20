#include "fonctions.h"

void write_log(char *action, int size, char *adresse)
{
    FILE *fichier;
    fichier = fopen("fichier.txt", "a");

    time_t timestamp = time(NULL);
    struct tm *pTime = localtime(&timestamp);

    char buffer[80];
    strftime(buffer, 80, "[%B %d %Y][%R]", pTime);
    fprintf(fichier, "%s %s %dbytes at adress %p\n", buffer, action, size, adresse);
    fclose(fichier);
}

void read_log()
{
    FILE *fichier;
    int taille;
    char adress[20];
    fichier = fopen("fichier.txt", "r");
    while (fscanf(fichier, "%*s %*s %*s %*s %dbytes at adress %s\n",
                  &taille, adress) == 2)
        printf("%s %dbytes\n", adress, taille);
    fclose(fichier);
}