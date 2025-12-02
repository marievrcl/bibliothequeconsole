//
// Created by Marie Viricel on 02/12/2025.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <util.h>
#include "emprunts.h"
#include "livres.h"


// -------------------- Fonctions auxiliaires --------------------

// Récupère la date actuelle au format "JJ/MM/AAAA"
void getDateAujourdhui(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// -------------------- Gestion des emprunts --------------------



void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *utilisateurs, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts) {
    int idUtilisateur=0;
    int idLivre=0;
    int dispo=0;
    char date[20];
    printf("Saisir IdUtilisateur");
    scanf("%d",&idUtilisateur);
    printf("Saisir IdLivre");
    scanf("%d",&idLivre);
    printf("Saisir date du jour de l'emprunt :");
    scanf("%g",&date);
    //Verifier disponibilite du livre
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == idLivre) {
            dispo=livres[i].disponible;
        }
    }
    if (dispo==0) {
        printf("Livre non disponible.\n");
        return;
    }

    emprunts[*nbEmprunts].idLivre = idLivre;
    emprunts[*nbEmprunts].idUtilisateur = idUtilisateur;
    emprunts[*nbEmprunts].dateEmprunt, date;
    emprunts[*nbEmprunts].dateRetour[0] = '\0';
    printf("L'emprunt a bien ete enregistre");
    (*nbEmprunts)++;

    // Mettre à jour la disponibilité
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == idLivre) {
            livres[i].disponible = 0;
            break;
        }
    }
}

void retournerLivre(Livre *livres,Emprunt *emprunts, int nbEmprunts, int idLivre, const char *dateRetour) {
    printf("entrer la date de retour");
    for (int i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == idLivre && emprunts[i].dateRetour[0] == '\0') {
            strncpy(emprunts[i].dateRetour, dateRetour, sizeof(emprunts[i].dateRetour)-1);
            emprunts[i].dateRetour[sizeof(emprunts[i].dateRetour)-1] = '\0';
            livres[i].disponible = 1;
            printf("L'emprunt a bien été retourné");
            break;
        }
    }
}

// Convertit JJ/MM/AAAA → struct tm
static int parseDate(const char *date, struct tm *out) {
    int j, m, a;
    if (sscanf(date, "%d/%d/%d", &j, &m, &a) != 3)
        return 0;

    memset(out, 0, sizeof(struct tm));
    out->tm_mday = j;
    out->tm_mon  = m - 1;   // 0–11
    out->tm_year = a - 1900;

    return 1;
}

int differenceJours(const char *d1, const char *d2) {
    struct tm t1, t2;

    if (!parseDate(d1, &t1)) return 0;
    if (!parseDate(d2, &t2)) return 0;

    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    double diff = difftime(time2, time1) / (60 * 60 * 24);

    return (int) diff;
}

// DeTECTION DE RETARDS (1 MOIS = 30 jours)
void detecterRetards(int nbEmprunts, Emprunt *emprunts) {

    char auj[20];
    dateAuj(auj);   //

    int found = 0;

    printf("\n===== EMPRUNTS EN RETARD (> 30 jours) =====\n");

    for (int i = 0; i < nbEmprunts; i++) {

        int jours;

        // Non rendu
        if (strcmp(emprunts[i].dateRetour, "-") == 0) {
            jours = differenceJours(emprunts[i].dateEmprunt, auj);
        }
        else { // Rendu
            jours = differenceJours(emprunts[i].dateEmprunt, emprunts[i].dateRetour);
        }

        if (jours > 30) {
            found = 1;

            printf("ISBN : %s | Utilisateur : %d | Emprunt : %s | Retour : %s | (%d jours)\n",
                   emprunts[i].idLivre,
                   emprunts[i].idUtilisateur,
                   emprunts[i].dateEmprunt,
                   emprunts[i].dateRetour,
                   jours);
        }
    }

    if (!found)
        printf("Aucun retard detecte.\n");
}

int calculerAmende(const char *dateE, const char *dateR) {
    int jours;

    if (strcmp(dateR, "-") == 0) {
        // Encore emprunté → comparer a aujourd’hui
        char auj[20];
        dateAuj(auj);
        jours = differenceJours(dateE, auj);
    } else {
        // Déja rendu
        jours = differenceJours(dateE, dateR);
    }

    int retard = jours - 30;
    if (retard <= 0) return 0;

    // 0.50€ par jour
    return retard * 0.5;
}

void afficherAmendes(int nbEmprunts, Emprunt *emprunts) {

    printf("\n========== AMENDES ==========\n");

    int found = 0;

    for (int i = 0; i < nbEmprunts; i++) {

        int amende = calculerAmende(emprunts[i].dateEmprunt, emprunts[i].dateRetour);

        if (amende > 0) {
            found = 1;
            printf("Utilisateur %d | ISBN %s | Amende : %.2f €\n",
                   emprunts[i].idLivre,
                   emprunts[i].idUtilisateur,
                   (float)amende);
        }
    }

    if (!found)
        printf("Aucune amende.\n");

    printf("================================\n");
}


