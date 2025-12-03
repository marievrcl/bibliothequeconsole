#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilisateurs.h"


// ================== FONCTIONS UTILITAIRES ==================

// Lit une ligne complète depuis l'entrée standard
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) {  // lit au maximum n-1 caractères depuis stdin
        buf[0] = '\0';                 // si fgets retourne NULL (fin de fichier ou erreur), on crée une chaîne vide
        return;                         // quitte la fonction
    }
    size_t len = strlen(buf);          // calcule la longueur de la chaîne lue
    if (len && buf[len-1] == '\n')    // si le dernier caractère est un retour à la ligne
        buf[len-1] = '\0';            // le remplace par '\0' pour supprimer le \n
}

// Compare deux chaînes de caractères insensibles à la casse
static int equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {                                  // tant que les deux chaînes ne sont pas terminées
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) // compare caractère par caractère
            return 0;                                   // retourne 0 si différent
        a++; b++;                                       // passe au caractère suivant
    }
    return *a == *b;                                    // retourne 1 si les deux chaînes sont terminées en même temps (égales)
}

// Cherche l'index d'un utilisateur par son email
static int indexUserParEmail(Utilisateur *users, int nb, const char *email) {
    for (int i = 0; i < nb; i++) {                      // parcourt tous les utilisateurs
        if (equalsIgnoreCase(users[i].email, email))    // compare l'email (insensible à la casse)
            return i;                                   // retourne l'index si trouvé
    }
    return -1;                                          // retourne -1 si non trouvé
}

// Cherche l'index d'un utilisateur par son ID
static int indexUserParId(Utilisateur *users, int nb, int id) {
    for (int i = 0; i < nb; i++)                       // parcourt tous les utilisateurs
        if (users[i].id == id)                         // compare l'id
            return i;                                  // retourne l'index si trouvé
    return -1;                                         // retourne -1 si non trouvé
}

// Calcule le prochain ID utilisateur à attribuer
static int nextUserId(Utilisateur *users, int nb) {
    int max = 0;                                       // initialise le max à 0
    for (int i = 0; i < nb; i++)                      // parcourt tous les utilisateurs
        if (users[i].id > max) max = users[i].id;     // met à jour le max si un id supérieur est trouvé
    return max + 1;                                   // retourne l'id suivant
}

// ================== FONCTIONS PUBLIQUES ==================

// Ajoute un nouvel utilisateur
void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    if (*nbUsers >= 100) {                             // vérifie si le tableau est plein
        printf("Nombre maximum d'utilisateurs atteint.\n");
        return;
    }

    char nom[50], prenom[50], email[100];             // variables temporaires pour la saisie

    printf("Nom : "); lireLigne(nom, sizeof(nom));     // lit le nom
    printf("Prénom : "); lireLigne(prenom, sizeof(prenom)); // lit le prénom
    printf("Email : "); lireLigne(email, sizeof(email));    // lit l'email

    if (indexUserParEmail(users, *nbUsers, email) >= 0) {   // vérifie si l'email est déjà utilisé
        printf("Cet email est déjà utilisé.\n");
        return;
    }

    Utilisateur u;                                     // crée une nouvelle structure Utilisateur
    u.id = nextUserId(users, *nbUsers);               // attribue un id automatique
    strncpy(u.nom, nom, sizeof(u.nom)); u.nom[49] = '\0';       // copie le nom et assure la terminaison
    strncpy(u.prenom, prenom, sizeof(u.prenom)); u.prenom[49] = '\0'; // copie le prénom
    strncpy(u.email, email, sizeof(u.email)); u.email[99] = '\0';      // copie l'email
    u.quota = 0;                                      // initialise le quota d'emprunts à 0

    users[*nbUsers] = u;                              // ajoute l'utilisateur au tableau
    (*nbUsers)++;                                     // incrémente le nombre d'utilisateurs

    printf("Utilisateur ajouté (ID=%d)\n", u.id);     // message de confirmation
}

// Supprime un utilisateur par ID
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    int idx = indexUserParId(users, *nbUsers, id);    // recherche l'utilisateur
    if (idx < 0) {                                    // si non trouvé
        printf("Utilisateur introuvable.\n");
        return;
    }

    // Décale tous les utilisateurs après l'index pour supprimer l'utilisateur
    for (int i = idx; i < (*nbUsers) - 1; i++)
        users[i] = users[i + 1];

    (*nbUsers)--;                                     // décrémente le nombre d'utilisateurs
    printf("Utilisateur supprimé.\n");               // message de confirmation
}

// Affiche tous les utilisateurs
void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    if (nbUsers == 0) {                               // si aucun utilisateur
        printf("Aucun utilisateur.\n");
        return;
    }

    printf("\n--- LISTE DES UTILISATEURS ---\n");     // en-tête du tableau
    printf("%-4s %-20s %-20s %-30s %s\n", "ID", "Nom", "Prénom", "Email", "Quota"); // titres colonnes
    for (int i = 0; i < nbUsers; i++) {              // parcourt tous les utilisateurs
        printf("%-4d %-20s %-20s %-30s %d\n",        // affiche les informations formatées
               users[i].id,
               users[i].nom,
               users[i].prenom,
               users[i].email,
               users[i].quota);
    }
}

// Authentification simplifiée
int authentifierUtilisateur(char *email) {
    return (email[0] != '\0');                        // retourne 1 si l'email n'est pas vide, sinon 0
}

