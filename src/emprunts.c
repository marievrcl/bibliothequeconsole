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
    time_t t = time(NULL);                 // Récupère le temps actuel
    struct tm tm = *localtime(&t);         // Convertit en structure tm locale
    sprintf(date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // Formate la date
}

// -------------------- Gestion des emprunts --------------------

// Fonction pour emprunter un livre
void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *utilisateurs, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts) {
    int idUtilisateur=0;                   // ID de l'utilisateur qui emprunte
    char isbn[20];                          // ISBN du livre
    int dispo=0;                             // Disponibilité du livre
    char date[20];                           // Date de l'emprunt

    printf("Saisir IdUtilisateur : ");
    scanf("%d", &idUtilisateur);           // Saisie de l'ID utilisateur

    // vider le buffer stdin pour éviter les problèmes avec fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Saisir ISBN : ");
    lireLigne(isbn, sizeof(isbn));         // Saisie de l'ISBN

    printf("Saisir date du jour de l'emprunt : ");
    lireLigne(date, sizeof(date));         // Saisie de la date

    // Vérifier disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            dispo = livres[i].disponible;  // Récupère le statut de disponibilité
        }
    }

    if (dispo == 0) {                      // Si le livre n'est pas dispo
        printf("Livre non disponible.\n");
        return;
    }

    // Enregistrer l'emprunt dans le tableau
    strcpy(emprunts[*nbEmprunts].isbn, isbn);
    emprunts[*nbEmprunts].idUtilisateur = idUtilisateur;
    strcpy(emprunts[*nbEmprunts].dateEmprunt, date);
    emprunts[*nbEmprunts].dateRetour[0] = '-';  // Indique que le livre n'est pas encore rendu

    printf("L'emprunt a bien été enregistré\n");
    (*nbEmprunts)++;                        // Incrémente le nombre total d'emprunts

    // Mettre à jour la disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            livres[i].disponible = 0;       // Livre emprunté → indisponible
            break;
        }
    }
}

// Fonction pour retourner un livre
void retournerLivre(Livre *livres, Emprunt *emprunts, int nbEmprunts, int nbLivres) {
    char dateR[20];                          // Date de retour
    char isbn[20];                            // ISBN du livre
    int id=0;                                 // ID utilisateur

    printf("ISBN du livre à retourner : ");
    lireLigne(isbn, sizeof(isbn));            // Saisie ISBN

    printf("IdUtilisateur : ");
    scanf("%d", &id);                         // Saisie ID utilisateur

    // vider le buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int x = -1;                               // Index de l'emprunt correspondant
    for (int i = 0; i < nbEmprunts; i++) {
        if (strcmp(emprunts[i].isbn, isbn) == 0 &&
            emprunts[i].idUtilisateur == id &&
            strcmp(emprunts[i].dateRetour, "-") == 0) {
            x = i;                            // Trouvé
            break;
        }
    }

    if (x < 0) {                              // Aucun emprunt correspondant
        printf("Aucun emprunt correspondant.\n");
        return;
    }

    printf("Entrer la date de retour : ");
    lireLigne(dateR, sizeof(dateR));          // Saisie de la date de retour

    strcpy(emprunts[x].dateRetour, dateR);    // Enregistre la date de retour

    // Mettre à jour la disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            livres[i].disponible = 1;         // Livre disponible à nouveau
            break;
        }
    }

    printf("Retour enregistré avec succès !\n");
}

// Convertit une date JJ/MM/AAAA en struct tm
static int parseDate(const char *date, struct tm *out) {
    int j, m, a;
    if (sscanf(date, "%d/%d/%d", &j, &m, &a) != 3) // Extraction des valeurs
        return 0;

    memset(out, 0, sizeof(struct tm));       // Initialise la struct tm
    out->tm_mday = j;
    out->tm_mon  = m - 1;                    // tm_mon : 0–11
    out->tm_year = a - 1900;                 // tm_year : années depuis 1900

    return 1;                                // Succès
}

// Calcule la différence en jours entre deux dates JJ/MM/AAAA
int differenceJours(const char *d1, const char *d2) {
    struct tm t1, t2;

    if (!parseDate(d1, &t1)) return 0;
    if (!parseDate(d2, &t2)) return 0;

    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    double diff = difftime(time2, time1) / (60 * 60 * 24); // Convertir secondes → jours
    return (int) diff;
}

// Détection des retards (> 30 jours)
void detecterRetards(int nbEmprunts, Emprunt *emprunts) {
    char auj[20];
    dateAuj(auj);                            // Date actuelle

    int found = 0;

    printf("\n===== EMPRUNTS EN RETARD (> 30 jours) =====\n");

    for (int i = 0; i < nbEmprunts; i++) {
        int jours;

        // Non rendu
        if (strcmp(emprunts[i].dateRetour, "-") == 0) {
            jours = differenceJours(emprunts[i].dateEmprunt, auj);
        } else { // Déjà rendu
            jours = differenceJours(emprunts[i].dateEmprunt, emprunts[i].dateRetour);
        }

        if (jours > 30) {                   // Retard détecté
            found = 1;
            printf("ISBN : %s | Utilisateur : %d | Emprunt : %s | Retour : %s | (%d jours)\n",
                   emprunts[i].isbn,
                   emprunts[i].idUtilisateur,
                   emprunts[i].dateEmprunt,
                   emprunts[i].dateRetour,
                   jours);
        }
    }

    if (!found)                               // Aucun retard
        printf("Aucun retard detecte.\n");
}

// Calcule l'amende pour un emprunt
int calculerAmende(const char *dateE, const char *dateR) {
    int jours;

    if (strcmp(dateR, "-") == 0) {            // Non rendu → comparer à aujourd'hui
        char auj[20];
        dateAuj(auj);
        jours = differenceJours(dateE, auj);
    } else {                                  // Déjà rendu
        jours = differenceJours(dateE, dateR);
    }

    int retard = jours - 30;                  // Retrait de la période gratuite de 30 jours
    if (retard <= 0) return 0;

    return retard * 0.5;                      // 0,50€ par jour de retard
}

// Affiche toutes les amendes
void afficherAmendes(int nbEmprunts, Emprunt *emprunts) {
    printf("\n========== AMENDES ==========\n");

    int found = 0;

    for (int i = 0; i < nbEmprunts; i++) {
        int amende = calculerAmende(emprunts[i].dateEmprunt, emprunts[i].dateRetour);

        if (amende > 0) {
            found = 1;
            printf("Utilisateur %d | ISBN %s | Amende : %.2f €\n",
                   emprunts[i].idUtilisateur,
                   emprunts[i].isbn,
                   (float)amende);
        }
    }

    if (!found)
        printf("Aucune amende.\n");

    printf("================================\n");
}
