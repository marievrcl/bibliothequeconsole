//
// Created by Marie Viricel on 02/12/2025.
//
#include <stdio.h>
#include <string.h>
#include "stats.h"
#include "emprunts.h"

// ---------------------------------------------------------
// Affiche les statistiques globales de la bibliothèque
// ---------------------------------------------------------
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres)
{
    printf("\n=== STATISTIQUES DE LA BIBLIOTHÈQUE ===\n"); // Titre du tableau de statistiques

    printf("Nombre total de livres : %d\n", nbLivres); // Affiche le nombre de livres
    printf("Nombre total d'utilisateurs : %d\n", nbUsers); // Affiche le nombre d'utilisateurs
    printf("Nombre total d'emprunts : %d\n", nbEmprunts); // Affiche le nombre total d'emprunts

    // Calcul du taux de disponibilité
    int dispo = 0; // Compteur pour les livres disponibles
    for (int i = 0; i < nbLivres; i++) // Parcourt tous les livres
        if (livres[i].disponible == 1) dispo++; // Incrémente si le livre est disponible

    float taux = (nbLivres > 0) ? ((float)dispo / nbLivres) * 100.0f : 0.0f; // Calcule le pourcentage de livres disponibles
    printf("Livres disponibles : %d (%.1f%%)\n", dispo, taux); // Affiche le nombre et le pourcentage

    // Affichage des détails avancés
    utilisateurLePlusActif(emprunts, nbEmprunts, users, nbUsers); // Affiche l'utilisateur le plus actif
    livresLesPlusEmpruntes(emprunts, nbEmprunts, livres, nbLivres); // Affiche le livre le plus emprunté

    printf("========================================\n"); // Ligne de séparation
}

// ---------------------------------------------------------
// Cherche l'utilisateur ayant réalisé le plus d'emprunts
// ---------------------------------------------------------
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers)
{
    if (nbEmprunts == 0 || nbUsers == 0) { // Si aucune donnée n'est disponible
        printf("Aucune donnée d'activité utilisateur.\n"); // Message d'absence de données
        return; // Sort de la fonction
    }

    int maxCount = 0; // Nombre maximum d'emprunts trouvés
    int idMax = -1;   // Index de l'utilisateur le plus actif

    // Pour chaque utilisateur
    for (int i = 0; i < nbUsers; i++) {
        int count = 0; // Compteur pour cet utilisateur

        // Parcourt tous les emprunts
        for (int j = 0; j < nbEmprunts; j++)
            if (emprunts[j].idUtilisateur == users[i].id) // Vérifie si l'emprunt correspond à cet utilisateur
                count++; // Incrémente le compteur

        if (count > maxCount) { // Si cet utilisateur a plus d'emprunts que le maximum actuel
            maxCount = count; // Met à jour le maximum
            idMax = i;        // Sauvegarde l'index de l'utilisateur
        }
    }

    if (idMax != -1) // Si un utilisateur a été trouvé
        printf("Utilisateur le plus actif : %s %s (%d emprunts)\n",
               users[idMax].prenom, users[idMax].nom, maxCount); // Affiche le résultat
}

// ---------------------------------------------------------
// Cherche le livre le plus emprunté
// ---------------------------------------------------------
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts, Livre *livres, int nbLivres)
{
    if (nbEmprunts == 0 || nbLivres == 0) { // Si aucune donnée n'est disponible
        printf("Aucune donnée d’emprunt disponible.\n"); // Message d'absence de données
        return; // Sort de la fonction
    }

    int count[100] = {0}; // Tableau des compteurs d'emprunts pour chaque livre, initialisé à 0

    // Parcourt tous les emprunts
    for (int i = 0; i < nbEmprunts; i++) {
        for (int j = 0; j < nbLivres; j++) {
            // Vérifie si l'ISBN de l'emprunt correspond à celui du livre
            if (emprunts[i].isbn == livres[j].isbn) // ⚠️ ici il faudrait strcmp pour comparer des chaînes
                count[j]++; // Incrémente le compteur pour ce livre
        }
    }

    int maxCount = 0; // Nombre maximum d'emprunts pour un livre
    int indexMax = -1; // Index du livre le plus emprunté

    // Cherche le livre avec le plus grand nombre d'emprunts
    for (int j = 0; j < nbLivres; j++) {
        if (count[j] > maxCount) {
            maxCount = count[j]; // Met à jour le maximum
            indexMax = j;        // Sauvegarde l'index
        }
    }

    if (indexMax != -1) // Si un livre a été trouvé
        printf("Livre le plus emprunté : \"%s\" de %s (%d emprunts)\n",
               livres[indexMax].titre, // Titre du livre
               livres[indexMax].auteur, // Auteur du livre
               maxCount);               // Nombre d'emprunts
}
