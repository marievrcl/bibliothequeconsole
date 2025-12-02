//
// Created by Marie Viricel on 02/12/2025.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
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
    strcpy(emprunts[*nbEmprunts].dateEmprunt, date); // Exemple
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

// DeTECTION DE RETARDS (1 MOIS = 30 jours)
void detecterRetards(void) {

    char auj[20];
    dateAuj(auj);   // Exemple : 30/11/2025

    int found = 0;

    printf("\n===== EMPRUNTS EN RETARD (> 30 jours) =====\n");

    for (int i = 0; i < nbEmprunts; i++) {

        int jours;

        // Non rendu
        if (strcmp(emprunts[i].dateR, "-") == 0) {
            jours = differenceJours(emprunts[i].dateE, auj);
        }
        else { // Rendu
            jours = differenceJours(emprunts[i].dateE, emprunts[i].dateR);
        }

        if (jours > 30) {
            found = 1;

            printf("ISBN : %s | Utilisateur : %d | Emprunt : %s | Retour : %s | (%d jours)\n",
                   emprunts[i].isbn,
                   emprunts[i].idUser,
                   emprunts[i].dateE,
                   emprunts[i].dateR,
                   jours);
        }
    }

    if (!found)
        printf("Aucun retard detecte.\n");
}

void afficherAmendes(void) {

    printf("\n========== AMENDES ==========\n");

    int found = 0;

    for (int i = 0; i < nbEmprunts; i++) {

        int amende = calculerAmende(emprunts[i].dateE, emprunts[i].dateR);

        if (amende > 0) {
            found = 1;
            printf("Utilisateur %d | ISBN %s | Amende : %.2f €\n",
                   emprunts[i].idUser,
                   emprunts[i].isbn,
                   (float)amende);
        }
    }

    if (!found)
        printf("Aucune amende.\n");

    printf("================================\n");
}


