//
// main.c
// Created by Marie Viricel on 02/12/2025.
//

#include <stdio.h>
#include <string.h>
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"
#include <util.h>

// ---------------------------------------------------------
// Fonction pour lancer le menu console
// ---------------------------------------------------------
void lancerMenuConsole() {
    // Déclaration des tableaux pour stocker les livres, utilisateurs et emprunts en mémoire
    Livre livres[100];
    Utilisateur utilisateurs[100];
    Emprunt emprunts[100];

    // Initialisation des compteurs pour le nombre de livres, utilisateurs et emprunts
    int nbLivres = 0, nbUsers = 0, nbEmprunts = 100; // nbEmprunts devrait probablement être 0 au départ

    // ========= CHARGEMENT DES DONNÉES =========
    chargerLivres(livres, &nbLivres);           // Charge les livres depuis "data/livres.txt"
    chargerUtilisateurs(utilisateurs, &nbUsers); // Charge les utilisateurs depuis "data/utilisateurs.txt"
    chargerEmprunts(emprunts, &nbEmprunts);     // Charge les emprunts depuis "data/emprunts.txt"

    int choix; // Variable pour stocker le choix du menu principal
    do {
        printf("\n=== MENU BIBLIOTHÈQUE ===\n"); // Affiche le menu principal
        printf("1. Gestion des livres\n");
        printf("2. Gestion des utilisateurs\n");
        printf("3. Gestion des emprunts\n");
        printf("4. Statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) choix = 0; // Lecture du choix utilisateur, si erreur → choix = 0
        int c; while ((c = getchar()) != '\n' && c != EOF) {} // Vide le buffer stdin

        switch (choix) {

            // =================== GESTION LIVRES ===================
            case 1: {
                int sousChoix; // Variable pour le sous-menu des livres
                do {
                    printf("\n--- GESTION DES LIVRES ---\n");
                    printf("1. Afficher les livres\n");
                    printf("2. Ajouter un livre\n");
                    printf("3. Modifier un livre\n");
                    printf("4. Supprimer un livre\n");
                    printf("5. Rechercher un livre\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sousChoix) != 1) sousChoix = 0; // Lecture du sous-choix
                    int d; while ((d = getchar()) != '\n' && d != EOF) {} // Vide le buffer

                    switch (sousChoix) {
                        case 1:
                            afficherLivres(livres, nbLivres); // Affiche tous les livres
                            break;
                        case 2:
                            ajouterLivre(livres, &nbLivres); // Ajoute un nouveau livre
                            break;
                        case 3: {
                            int id; // ID du livre à modifier
                            printf("ID du livre à modifier : ");
                            if (scanf("%d", &id) == 1) { // Lecture de l'ID
                                int e; while ((e = getchar()) != '\n' && e != EOF) {} // Vide le buffer
                                modifierLivre(livres, nbLivres, id); // Modifie le livre correspondant
                            }
                            break;
                        }
                        case 4: {
                            int id; // ID du livre à supprimer
                            printf("ID du livre à supprimer : ");
                            if (scanf("%d", &id) == 1)
                                supprimerLivre(livres, &nbLivres, id); // Supprime le livre correspondant
                            break;
                        }
                        case 5: {
                            char titre[100]; // Titre du livre à rechercher
                            printf("Entrez le titre à rechercher : ");
                            if (!fgets(titre, sizeof(titre), stdin)) { // Lecture du titre
                                printf("Erreur de lecture.\n");
                                break;
                            }
                            titre[strcspn(titre, "\n")] = 0;  // Supprime le retour chariot final

                            int idx = rechercherLivre(livres, nbLivres, titre); // Recherche du livre par titre exact
                            if (idx >= 0) {
                                printf("Livre trouvé : ID=%d, Titre=%s, Auteur=%s\n",
                                       livres[idx].id, livres[idx].titre, livres[idx].auteur); // Affiche le livre trouvé
                            } else {
                                printf("Livre non trouvé.\n"); // Aucun livre trouvé
                            }
                            break;
                        }
                        case 0: // Retour au menu principal
                            break;
                        default:
                            printf("Choix invalide.\n"); // Gestion d'une saisie incorrecte
                    }
                } while (sousChoix != 0); // Boucle jusqu'à retour
                break;
            }

            // =================== GESTION UTILISATEURS ===================
            case 2: {
                int sous; // Variable pour le sous-menu des utilisateurs
                do {
                    printf("\n--- GESTION DES UTILISATEURS ---\n");
                    printf("1. Afficher les utilisateurs\n");
                    printf("2. Ajouter un utilisateur\n");
                    printf("3. Supprimer un utilisateur\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sous) != 1) sous = 0; // Lecture du sous-choix
                    int d; while ((d = getchar()) != '\n' && d != EOF) {} // Vide le buffer

                    switch (sous) {
                        case 1:
                            afficherUtilisateurs(utilisateurs, nbUsers); // Affiche tous les utilisateurs
                            break;
                        case 2:
                            ajouterUtilisateur(utilisateurs, &nbUsers); // Ajoute un nouvel utilisateur
                            break;
                        case 3: {
                            int id; // ID de l'utilisateur à supprimer
                            printf("ID de l'utilisateur à supprimer : ");
                            if (scanf("%d", &id) == 1)
                                supprimerUtilisateur(utilisateurs, &nbUsers, id); // Supprime l'utilisateur correspondant
                            break;
                        }
                        case 0: // Retour au menu principal
                            break;
                        default:
                            printf("Choix invalide.\n"); // Gestion d'une saisie incorrecte
                    }
                } while (sous != 0); // Boucle jusqu'à retour
                break;
            }

            // =================== GESTION EMPRUNTS ===================
            case 3: {
                int sous; // Variable pour le sous-menu des emprunts
                do {
                    printf("\n--- GESTION DES EMPRUNTS ---\n");
                    printf("1. Emprunter un livre\n");
                    printf("2. Retourner un livre\n");
                    printf("3. Vérifier les emprunts non rendus\n");
                    printf("4. Afficher les amendes\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if(scanf("%d",&sous)!=1) sous=0; // Lecture du sous-choix
                    int d; while((d=getchar())!='\n' && d!=EOF){} // Vide le buffer

                    switch(sous){
                        case 1:
                            emprunterLivre(livres, nbLivres, utilisateurs, nbUsers, emprunts, &nbEmprunts); // Emprunter un livre
                            break;
                        case 2:
                            retournerLivre(livres, emprunts, nbEmprunts, nbLivres); // Retourner un livre
                            break;
                        case 3:
                            detecterRetards(nbEmprunts, emprunts); // Affiche les emprunts en retard
                            break;
                        case 4:  // <- nouvelle option
                            afficherAmendes(nbEmprunts, emprunts);
                            break;
                        case 0: break; // Retour au menu principal
                        default: printf("Choix invalide.\n"); // Gestion d'une saisie incorrecte
                    }
                } while(sous!=0); // Boucle jusqu'à retour
                break;
            }

            // =================== STATISTIQUES ===================
            case 4:
                afficherStatistiques(emprunts, nbEmprunts,
                                     utilisateurs, nbUsers,
                                     livres, nbLivres); // Affiche les statistiques globales
                break;

            // =================== QUITTER ===================
            case 0:
                printf("Sauvegarde et fermeture...\n"); // Message de fermeture
                break;

            default:
                printf("Choix invalide.\n"); // Gestion d'une saisie incorrecte
        }

    } while (choix != 0); // Boucle jusqu'à ce que l'utilisateur choisisse de quitter

    // ========= SAUVEGARDE =========
    sauvegarderLivres(livres, nbLivres);           // Sauvegarde les livres dans "data/livres.txt"
    sauvegarderUtilisateurs(utilisateurs, nbUsers); // Sauvegarde les utilisateurs
    sauvegarderEmprunts(emprunts, nbEmprunts);     // Sauvegarde les emprunts
}

// ---------------------------------------------------------
// Fonction main
// ---------------------------------------------------------
int main(void) {
    printf("Bienvenue dans la bibliothèque console !\n"); // Message d'accueil
    lancerMenuConsole(); // Lance le menu principal
    return 0; // Fin du programme
}



