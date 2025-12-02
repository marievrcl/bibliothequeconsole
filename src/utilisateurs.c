#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilisateurs.h"

// ================== FONCTIONS UTILITAIRES ==================

// Lit une ligne complète au clavier
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) { buf[0] = '\0'; return; }
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
}

// Compare deux chaînes insensibles à la casse
static int equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++; b++;
    }
    return *a == *b;
}

// Cherche un utilisateur par son email
static int indexUserParEmail(Utilisateur *users, int nb, const char *email) {
    for (int i = 0; i < nb; i++) {
        if (equalsIgnoreCase(users[i].email, email))
            return i;
    }
    return -1;
}

// Cherche un utilisateur par son id
static int indexUserParId(Utilisateur *users, int nb, int id) {
    for (int i = 0; i < nb; i++)
        if (users[i].id == id)
            return i;
    return -1;
}

// Calcule le prochain id utilisateur
static int nextUserId(Utilisateur *users, int nb) {
    int max = 0;
    for (int i = 0; i < nb; i++)
        if (users[i].id > max) max = users[i].id;
    return max + 1;
}

// ================== FONCTIONS PUBLIQUES ==================

// Ajoute un nouvel utilisateur
void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    if (*nbUsers >= 100) {
        printf("Nombre maximum d'utilisateurs atteint.\n");
        return;
    }

    char nom[50], prenom[50], email[100];

    printf("Nom : "); lireLigne(nom, sizeof(nom));
    printf("Prénom : "); lireLigne(prenom, sizeof(prenom));
    printf("Email : "); lireLigne(email, sizeof(email));

    if (indexUserParEmail(users, *nbUsers, email) >= 0) {
        printf("Cet email est déjà utilisé.\n");
        return;
    }

    Utilisateur u;
    u.id = nextUserId(users, *nbUsers);
    strncpy(u.nom, nom, sizeof(u.nom)); u.nom[49] = '\0';
    strncpy(u.prenom, prenom, sizeof(u.prenom)); u.prenom[49] = '\0';
    strncpy(u.email, email, sizeof(u.email)); u.email[99] = '\0';
    u.quota = 0;

    users[*nbUsers] = u;
    (*nbUsers)++;

    printf("Utilisateur ajouté (ID=%d)\n", u.id);
}

// Supprime un utilisateur par id
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    int idx = indexUserParId(users, *nbUsers, id);
    if (idx < 0) {
        printf("Utilisateur introuvable.\n");
        return;
    }

    // Décale le tableau
    for (int i = idx; i < (*nbUsers) - 1; i++)
        users[i] = users[i + 1];

    (*nbUsers)--;
    printf("Utilisateur supprimé.\n");
}

// Affiche tous les utilisateurs
void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    if (nbUsers == 0) {
        printf("Aucun utilisateur.\n");
        return;
    }

    printf("\n--- LISTE DES UTILISATEURS ---\n");
    printf("%-4s %-20s %-20s %-30s %s\n", "ID", "Nom", "Prénom", "Email", "Quota");
    for (int i = 0; i < nbUsers; i++) {
        printf("%-4d %-20s %-20s %-30s %d\n",
               users[i].id,
               users[i].nom,
               users[i].prenom,
               users[i].email,
               users[i].quota);
    }
}

// Authentification simplifiée
int authentifierUtilisateur(char *email) {
    return (email[0] != '\0');
}

