//
// Created by Marie Viricel on 02/12/2025.
//
//
// Created by Marie Viricel on 02/12/2025.
//

//
// Created by Marie Viricel on 02/12/2025.
//

#ifndef BIBLIOTHEQUECONSOLE_UTILISATEURS_H
#define BIBLIOTHEQUECONSOLE_UTILISATEURS_H

#endif //BIBLIOTHEQUECONSOLE_UTILISATEURS_H

//
// Module de gestion des utilisateurs : structure Utilisateur
// et fonctions pour ajouter, afficher et supprimer des utilisateurs.
//

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

// Représente un utilisateur de la bibliothèque
typedef struct {
    int  id;          // Identifiant unique de l'utilisateur
    char nom[50];     // Nom de l'utilisateur
    char prenom[50];  // Prénom de l'utilisateur
    char email[100];  // Adresse email (unique et insensible à la casse)
    int  quota;       // Nombre de livres actuellement empruntés
} Utilisateur;

/**
 * Ajoute un nouvel utilisateur dans le tableau users.
 * - Génère un ID automatique
 * - Saisit le nom, le prénom et l'email
 * - Vérifie que l'email n'est pas déjà utilisé (insensible à la casse)
 * @param users Tableau des utilisateurs existants
 * @param nbUsers Pointeur vers le nombre d'utilisateurs (sera incrémenté)
 */
void ajouterUtilisateur(Utilisateur *users, int *nbUsers);

/**
 * Supprime un utilisateur à partir de son ID.
 * Décale les éléments du tableau pour combler le vide.
 * @param users Tableau des utilisateurs
 * @param nbUsers Pointeur vers le nombre d'utilisateurs
 * @param id ID de l'utilisateur à supprimer
 */
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id);

/**
 * Affiche la liste complète des utilisateurs sous forme de tableau.
 * @param users Tableau des utilisateurs
 * @param nbUsers Nombre d'utilisateurs
 */
void afficherUtilisateurs(Utilisateur *users, int nbUsers);

/**
 * Fonction d'authentification simplifiée.
 * Pour l'instant, renvoie 1 si l'email n'est pas vide.
 * @param email Email à authentifier
 * @return 1 si authentifié, 0 sinon
 */
int authentifierUtilisateur(char *email);

#endif // UTILISATEURS_H
// Fin de la protection contre inclusion multiple