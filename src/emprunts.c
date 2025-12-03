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
    time_t t = time(NULL);                       // Récupère le temps actuel en secondes depuis 1970
    struct tm tm = *localtime(&t);              // Convertit le temps en structure locale tm
    sprintf(date, "%02d/%02d/%04d",              // Formate la date dans la chaîne passée en paramètre
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Convertit une date JJ/MM/AAAA en struct tm
static int parseDate(const char *date, struct tm *out) {
    int j, m, a;                                 // Variables pour jour, mois et année
    if (sscanf(date, "%d/%d/%d", &j, &m, &a) != 3) // Extraction de jour/mois/année
        return 0;                                // Retourne 0 si la date est invalide

    memset(out, 0, sizeof(struct tm));          // Initialise toute la structure à 0
    out->tm_mday = j;                            // Affecte le jour
    out->tm_mon  = m - 1;                        // Affecte le mois (0–11)
    out->tm_year = a - 1900;                     // Affecte l'année depuis 1900

    return 1;                                    // Retourne 1 si la conversion a réussi
}

// Calcule la différence en jours entre deux dates JJ/MM/AAAA
int differenceJours(const char *d1, const char *d2) {
    struct tm t1, t2;                            // Structures tm pour chaque date

    if (!parseDate(d1, &t1)) return 0;           // Convertit d1 en tm, retourne 0 si erreur
    if (!parseDate(d2, &t2)) return 0;           // Convertit d2 en tm, retourne 0 si erreur

    time_t time1 = mktime(&t1);                  // Convertit tm en time_t
    time_t time2 = mktime(&t2);                  // Convertit tm en time_t

    double diff = difftime(time2, time1) / (60 * 60 * 24); // Différence en jours
    return (int) diff;                            // Retourne la différence en entier
}

// -------------------- Gestion des emprunts --------------------

// Fonction pour emprunter un livre
void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *utilisateurs, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts) {
    int idUtilisateur = 0;                        // ID de l'utilisateur emprunteur
    char isbn[20];                                 // ISBN du livre
    int dispo = 0;                                 // Disponibilité du livre
    char date[20];                                 // Date de l'emprunt

    printf("Saisir IdUtilisateur : ");            // Demande l'ID utilisateur
    scanf("%d", &idUtilisateur);                  // Lit l'ID depuis l'entrée

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Vide le buffer stdin

    printf("Saisir ISBN : ");                     // Demande l'ISBN
    lireLigne(isbn, sizeof(isbn));                // Lit l'ISBN avec fgets ou équivalent

    printf("Saisir date du jour de l'emprunt : "); // Demande la date
    lireLigne(date, sizeof(date));                // Lit la date

    // Vérifier disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) { // Compare l'ISBN
            dispo = livres[i].disponible;        // Récupère la disponibilité
            break;                                // Sort de la boucle
        }
    }

    if (dispo == 0) {                             // Si livre indisponible
        printf("Livre non disponible.\n");        // Affiche message
        return;                                   // Quitte la fonction
    }

    // Enregistrer l'emprunt
    strcpy(emprunts[*nbEmprunts].isbn, isbn);     // Copie l'ISBN
    emprunts[*nbEmprunts].idUtilisateur = idUtilisateur; // Stocke l'ID utilisateur
    strcpy(emprunts[*nbEmprunts].dateEmprunt, date); // Stocke la date d'emprunt
    strcpy(emprunts[*nbEmprunts].dateRetour, "-"); // Indique que le livre n'est pas rendu

    (*nbEmprunts)++;                              // Incrémente le compteur d'emprunts

    // Mettre à jour disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            livres[i].disponible = 0;            // Livre maintenant indisponible
            break;                                // Sort de la boucle
        }
    }

    printf("L'emprunt a bien été enregistré.\n"); // Message de confirmation
}

// Fonction pour retourner un livre
void retournerLivre(Livre *livres, Emprunt *emprunts, int nbEmprunts, int nbLivres) {
    char dateR[20];                                // Date de retour
    char isbn[20];                                 // ISBN du livre
    int id = 0;                                    // ID utilisateur

    printf("ISBN du livre à retourner : ");
    lireLigne(isbn, sizeof(isbn));                 // Lit l'ISBN

    printf("IdUtilisateur : ");
    scanf("%d", &id);                              // Lit l'ID utilisateur

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Vide le buffer stdin

    int x = -1;                                    // Index de l'emprunt correspondant
    for (int i = 0; i < nbEmprunts; i++) {
        if (strcmp(emprunts[i].isbn, isbn) == 0 &&  // Vérifie ISBN
            emprunts[i].idUtilisateur == id &&     // Vérifie ID utilisateur
            strcmp(emprunts[i].dateRetour, "-") == 0) { // Vérifie si pas encore rendu
            x = i;                                  // Stocke l'index
            break;                                  // Sort de la boucle
        }
    }

    if (x < 0) {                                   // Si aucun emprunt trouvé
        printf("Aucun emprunt correspondant.\n");
        return;                                    // Quitte la fonction
    }

    printf("Entrer la date de retour : ");
    lireLigne(dateR, sizeof(dateR));               // Lit la date de retour

    strcpy(emprunts[x].dateRetour, dateR);        // Enregistre la date de retour

    // Mettre à jour disponibilité du livre
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            livres[i].disponible = 1;             // Livre maintenant disponible
            break;                                 // Sort de la boucle
        }
    }

    printf("Retour enregistré avec succès !\n");   // Message de confirmation
}

// -------------------- Gestion des retards et amendes --------------------

// Détection des retards (> 30 jours)
void detecterRetards(int nbEmprunts, Emprunt *emprunts) {
    char auj[20];                                 // Chaîne pour stocker la date d'aujourd'hui
    getDateAujourdhui(auj);                       // Remplit la date actuelle

    int found = 0;                                // Indique si un retard est trouvé
    printf("\n===== EMPRUNTS EN RETARD (> 30 jours) =====\n");

    for (int i = 0; i < nbEmprunts; i++) {
        int jours;                                 // Nombre de jours d'emprunt
        if (strcmp(emprunts[i].dateRetour, "-") == 0) // Livre non rendu
            jours = differenceJours(emprunts[i].dateEmprunt, auj);
        else                                        // Livre déjà rendu
            jours = differenceJours(emprunts[i].dateEmprunt, emprunts[i].dateRetour);

        if (jours > 30) {                          // Si retard > 30 jours
            found = 1;
            printf("ISBN : %s | Utilisateur : %d | Emprunt : %s | Retour : %s | (%d jours)\n",
                   emprunts[i].isbn,
                   emprunts[i].idUtilisateur,
                   emprunts[i].dateEmprunt,
                   emprunts[i].dateRetour,
                   jours);
        }
    }

    if (!found)                                    // Aucun retard trouvé
        printf("Aucun retard detecte.\n");
}

// Calcule l'amende pour un emprunt
float calculerAmende(const char *dateEmprunt, const char *dateRetour) {
    int jours;                                     // Nombre de jours d'emprunt

    if (strcmp(dateRetour, "-") == 0) {           // Livre non rendu
        char auj[20];
        getDateAujourdhui(auj);                   // Date actuelle
        jours = differenceJours(dateEmprunt, auj);
    } else {                                      // Livre déjà rendu
        jours = differenceJours(dateEmprunt, dateRetour);
    }

    int retard = jours - 30;                       // Période gratuite = 30 jours
    if (retard <= 0) return 0.0f;                 // Pas d'amende si pas de retard

    return retard * 0.5f;                          // Amende 0,50€ par jour
}

// Affiche toutes les amendes
void afficherAmendes(int nbEmprunts, Emprunt *emprunts) {
    printf("\n========== AMENDES ==========\n");
    int found = 0;                                 // Indique si une amende existe

    for (int i = 0; i < nbEmprunts; i++) {
        float amende = calculerAmende(emprunts[i].dateEmprunt, emprunts[i].dateRetour); // Calcule amende

        if (amende > 0.0f) {                      // Si amende > 0
            found = 1;
            printf("Utilisateur %d | ISBN %s | Amende : %.2f €\n",
                   emprunts[i].idUtilisateur,
                   emprunts[i].isbn,
                   amende);
        }
    }

    if (!found)                                    // Si aucune amende
        printf("Aucune amende.\n");

    printf("================================\n"); // Fin de l'affichage des amendes
}
