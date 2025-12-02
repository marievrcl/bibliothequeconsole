//
// Created by Marie Viricel on 02/12/2025.
//
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

//Lire une ligne sans garder le retour à la ligne
void lireLigne(char *buf, int n) { // lit au max n-1 caractère depuis l'entré standard et les stock dans buf
    if (!fgets(buf, n, stdin)) { buf[0] = '\0'; return; } // si fgets retourne null( fin de fichier) on met buf[0] = '\0' pour avoir une chaîne vide et on quitte la fonction.
    size_t l = strlen(buf); // calcule la longueur de la chaîne lue.
    if (l>0 && buf[l-1]=='\n') buf[l-1] = '\0'; //Supprime le caractère de nouvelle ligne si présent à la fin de la saisie.
}

//mettre la date du jour dans buffer sous la forme jj/mm/aaaa.
void dateAuj(char *buffer) {
    time_t now = time(NULL); //récupère le temps actuel en secondes depuis le 1er janvier 1970
    struct tm *t = localtime(&now); //convertit now en structure contenant jour, mois, année

    sprintf(buffer, "%02d/%02d/%04d",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900); //jour du mois (1–31), mois (0–11 dans struct tm, donc on ajoute 1), année (nombre d’années depuis 1900)
}

//calculer le nombre de jours écoulés depuis une date donnée.
int joursDepuis(const char *date) {
    int j=0,m=0,a=0;
    if (sscanf(date,"%d/%d/%d",&j,&m,&a)!=3) return 0; //lit jour/mois/année depuis la chaîne date. Si on ne récupère pas les 3 valeurs, on retourne 0.
    struct tm d = {0}; //initialise une structure pour représenter la date.
    d.tm_mday = j; d.tm_mon = m-1; d.tm_year = a-1900; //conversion dans le format struct tm. Les mois commencent à 0, les années à 1900.
    time_t t1 = mktime(&d); //convertit struct tm en nombre de secondes depuis 1970.
    time_t t2 = time(NULL);
    return (int)((t2 - t1) / 86400); //différence en secondes convertie en jours (86400 = 24h × 3600s).
}