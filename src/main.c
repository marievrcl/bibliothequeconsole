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
    // Tableaux statiques pour stocker les données en mémoire
    Livre livres[100];
    Utilisateur utilisateurs[100];
    Emprunt emprunts[100];

    int nbLivres = 0, nbUsers = 0, nbEmprunts = 100;

    // ========= CHARGEMENT DES DONNÉES =========
    chargerLivres(livres, &nbLivres);
    chargerUtilisateurs(utilisateurs, &nbUsers);
    chargerEmprunts(emprunts, &nbEmprunts);

    int choix;
    do {
        printf("\n=== MENU BIBLIOTHÈQUE ===\n");
        printf("1. Gestion des livres\n");
        printf("2. Gestion des utilisateurs\n");
        printf("3. Gestion des emprunts\n");
        printf("4. Statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) choix = 0;
        int c; while ((c = getchar()) != '\n' && c != EOF) {}

        switch (choix) {

            // =================== GESTION LIVRES ===================
            case 1: {
                int sousChoix;
                do {
                    printf("\n--- GESTION DES LIVRES ---\n");
                    printf("1. Afficher les livres\n");
                    printf("2. Ajouter un livre\n");
                    printf("3. Modifier un livre\n");
                    printf("4. Supprimer un livre\n");
                    printf("5. Rechercher un livre\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sousChoix) != 1) sousChoix = 0;
                    int d; while ((d = getchar()) != '\n' && d != EOF) {}

                    switch (sousChoix) {
                        case 1:
                            afficherLivres(livres, nbLivres);
                            break;
                        case 2:
                            ajouterLivre(livres, &nbLivres);
                            break;
                        case 3: {
                            int id;
                            printf("ID du livre à modifier : ");
                            if (scanf("%d", &id) == 1) {
                                int e; while ((e = getchar()) != '\n' && e != EOF) {}
                                modifierLivre(livres, nbLivres, id);
                            }
                            break;
                        }
                        case 4: {
                            int id;
                            printf("ID du livre à supprimer : ");
                            if (scanf("%d", &id) == 1)
                                supprimerLivre(livres, &nbLivres, id);
                            break;
                        }
                        case 5: {
                            char titre[100];
                            printf("Entrez le titre à rechercher : ");
                            if (!fgets(titre, sizeof(titre), stdin)) {
                                printf("Erreur de lecture.\n");
                                break;
                            }
                            titre[strcspn(titre, "\n")] = 0;  // supprime le \n final

                            int idx = rechercherLivre(livres, nbLivres, titre);
                            if (idx >= 0) {
                                printf("Livre trouvé : ID=%d, Titre=%s, Auteur=%s\n",
                                       livres[idx].id, livres[idx].titre, livres[idx].auteur);
                            } else {
                                printf("Livre non trouvé.\n");
                            }
                            break;
                        }
                        case 0:
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                } while (sousChoix != 0);
                break;
            }

            // =================== GESTION UTILISATEURS ===================
            case 2: {
                int sous;
                do {
                    printf("\n--- GESTION DES UTILISATEURS ---\n");
                    printf("1. Afficher les utilisateurs\n");
                    printf("2. Ajouter un utilisateur\n");
                    printf("3. Supprimer un utilisateur\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sous) != 1) sous = 0;
                    int d; while ((d = getchar()) != '\n' && d != EOF) {}

                    switch (sous) {
                        case 1:
                            afficherUtilisateurs(utilisateurs, nbUsers);
                            break;
                        case 2:
                            ajouterUtilisateur(utilisateurs, &nbUsers);
                            break;
                        case 3: {
                            int id;
                            printf("ID de l'utilisateur à supprimer : ");
                            if (scanf("%d", &id) == 1)
                                supprimerUtilisateur(utilisateurs, &nbUsers, id);
                            break;
                        }
                        case 0:
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                } while (sous != 0);
                break;
            }

            // =================== GESTION EMPRUNTS ===================
            case 3: {
                int sous;
                do {
                    printf("\n--- GESTION DES EMPRUNTS ---\n");
                    printf("1. Emprunter un livre\n");
                    printf("2. Retourner un livre\n");
                    printf("3. Vérifier les emprunts non rendus\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if(scanf("%d",&sous)!=1) sous=0;
                    int d; while((d=getchar())!='\n' && d!=EOF){}

                    switch(sous){
                        case 1:
                            // exemple : emprunter le livre avec idLivre et idUtilisateur
                            emprunterLivre(livres, nbLivres, utilisateurs, nbUsers, emprunts, &nbEmprunts);
                            break;
                        case 2: {
                            int idLivre;
                                char dateRetour[11];
                                fgets(dateRetour, sizeof(dateRetour), stdin);
                                dateRetour[strcspn(dateRetour, "\n")] = 0; // enlever \n
                                retournerLivre(livres,emprunts, nbEmprunts, idLivre, dateRetour);
                            break;
                        }


                        case 3:
                            detecterRetards(nbEmprunts,emprunts);
                            break;
                        case 0: break;
                        default: printf("Choix invalide.\n");
                    }
                } while(sous!=0);
                break;
            }

            // =================== STATISTIQUES ===================
            case 4:
                afficherStatistiques(emprunts, nbEmprunts,
                                     utilisateurs, nbUsers,
                                     livres, nbLivres);
                break;

            // =================== QUITTER ===================
            case 0:
                printf("Sauvegarde et fermeture...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    // ========= SAUVEGARDE =========
    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);
}

// ---------------------------------------------------------
// Fonction main
// ---------------------------------------------------------
int main(void) {
    printf("Bienvenue dans la bibliothèque console !\n");
    lancerMenuConsole();
    return 0;
}



