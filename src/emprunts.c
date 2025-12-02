//
// Created by Marie Viricel on 02/12/2025.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "emprunts.h"
#include "livres.h"
#include "utilisateurs.h"

// ---------------------------------------------------------
// Emprunter un livre
// ---------------------------------------------------------
void emprunterLivre(Livre livres[], int nbLivres, Utilisateur utilisateurs[], int nbUsers,
                    Emprunt emprunts[], int *nbEmprunts) {
    int idLivre, idUser;
    char date[11];

    printf("ID du livre à emprunter : ");
    if (scanf("%d", &idLivre) != 1) return;
    printf("ID de l'utilisateur : ");
    if (scanf("%d", &idUser) != 1) return;

    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    // Vérifier si le livre est disponible
    int livreDispo = 0;
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == idLivre && livres[i].disponible) {
            livreDispo = 1;
            livres[i].disponible = 0;
            break;
        }
    }
    if (!livreDispo) {
        printf("Livre non disponible.\n");
        return;
    }

    // Date d'emprunt (aujourd'hui)
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, sizeof(date), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Ajouter l'emprunt
    if (*nbEmprunts >= MAX_EMPRUNTS) {
        printf("Nombre maximum d'emprunts atteint.\n");
        return;
    }
    emprunts[*nbEmprunts].idLivre = idLivre;
    emprunts[*nbEmprunts].idUtilisateur = idUser;
    strncpy(emprunts[*nbEmprunts].dateEmprunt, date, 11);
    emprunts[*nbEmprunts].dateRetour[0] = '\0';
    (*nbEmprunts)++;

    printf("Emprunt enregistré : Livre %d pour utilisateur %d\n", idLivre, idUser);
}

// ---------------------------------------------------------
// Retourner un livre
// ---------------------------------------------------------
void retournerLivre(Emprunt emprunts[], int nbEmprunts, int idLivre, const char *dateRetour) {
    int found = 0;
    for (int i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == idLivre && emprunts[i].dateRetour[0] == '\0') {
            strncpy(emprunts[i].dateRetour, dateRetour, 11);
            printf("Livre ID %d retourné le %s\n", idLivre, dateRetour);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Livre ID %d non trouvé parmi les emprunts en cours.\n", idLivre);
    }
}

// ---------------------------------------------------------
// Afficher tous les emprunts
// ---------------------------------------------------------
void afficherEmprunts(const Emprunt emprunts[], int nbEmprunts,
                      const Livre livres[], int nbLivres,
                      const Utilisateur utilisateurs[], int nbUsers) {
    for (int i = 0; i < nbEmprunts; i++) {
        const char *titre = "Inconnu";
        const char *nomUser = "Inconnu";

        for (int j = 0; j < nbLivres; j++) {
            if (livres[j].id == emprunts[i].idLivre) {
                titre = livres[j].titre;
                break;
            }
        }

        for (int j = 0; j < nbUsers; j++) {
            if (utilisateurs[j].id == emprunts[i].idUtilisateur) {
                nomUser = utilisateurs[j].nom;
                break;
            }
        }

        printf("Livre : %s | Utilisateur : %s | Emprunt : %s | Retour : %s\n",
               titre, nomUser,
               emprunts[i].dateEmprunt,
               emprunts[i].dateRetour[0] ? emprunts[i].dateRetour : "Non retourné");
    }
}

// ---------------------------------------------------------
// Vérifier retards
// ---------------------------------------------------------
void verifierRetards(const Emprunt emprunts[], int nbEmprunts) {
    printf("Vérification des retards :\n");
    for (int i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].dateRetour[0] == '\0') {
            printf("Livre ID %d non rendu (emprunt du %s)\n",
                   emprunts[i].idLivre, emprunts[i].dateEmprunt);
        }
    }
}










