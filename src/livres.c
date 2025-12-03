//
// Created by Marie Viricel on 02/12/2025.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "livres.h"

// ---------------------------------------------------------
// Ajouter un livre
// ---------------------------------------------------------
void ajouterLivre(Livre *livres, int *nbLivres) {
    Livre *l = &livres[*nbLivres];          // Pointeur sur la prochaine case libre du tableau

    // Génère un ID automatique : si tableau vide → 1, sinon +1 par rapport au dernier
    l->id = (*nbLivres > 0) ? livres[*nbLivres-1].id + 1 : 1;

    // Saisie du titre
    printf("Titre : ");
    fgets(l->titre, sizeof(l->titre), stdin); // Lit la ligne
    l->titre[strcspn(l->titre, "\n")] = 0;   // Supprime le '\n' final

    // Saisie de l'auteur
    printf("Auteur : ");
    fgets(l->auteur, sizeof(l->auteur), stdin);
    l->auteur[strcspn(l->auteur, "\n")] = 0;

    // Saisie de la catégorie
    printf("Catégorie : ");
    fgets(l->categorie, sizeof(l->categorie), stdin);
    l->categorie[strcspn(l->categorie, "\n")] = 0;

    // Saisie de l'ISBN
    printf("ISBN : ");
    fgets(l->isbn, sizeof(l->isbn), stdin);
    l->isbn[strcspn(l->isbn, "\n")] = 0;

    // Saisie de l'année
    printf("Année de publication : ");
    scanf("%d", &l->annee);
    int c; while ((c=getchar())!='\n' && c!=EOF) {} // vide le buffer

    l->disponible = 1;                       // Livre disponible par défaut

    (*nbLivres)++;                            // Incrémente le compteur
    printf("Livre ajouté avec succès.\n");
}

// ---------------------------------------------------------
// Supprimer un livre
// ---------------------------------------------------------
void supprimerLivre(Livre *livres, int *nbLivres, int id) {
    int i, trouve = 0;
    // Cherche le livre par ID
    for (i = 0; i < *nbLivres; i++) {
        if (livres[i].id == id) {
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("Livre non trouvé.\n");
        return;
    }
    // Décale tous les livres après le livre supprimé
    for (int j = i; j < *nbLivres-1; j++)
        livres[j] = livres[j+1];
    (*nbLivres)--;
    printf("Livre supprimé.\n");
}

// ---------------------------------------------------------
// Modifier un livre
// ---------------------------------------------------------
void modifierLivre(Livre *livres, int nbLivres, int id) {
    int i, trouve = 0;
    // Cherche le livre par ID
    for (i = 0; i < nbLivres; i++) {
        if (livres[i].id == id) {
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("Livre non trouvé.\n");
        return;
    }

    Livre *l = &livres[i]; // Pointeur sur le livre à modifier
    char tmp[100];

    // Modification titre (si saisie vide, ne change pas)
    printf("Modifier titre (%s) : ", l->titre);
    fgets(tmp, sizeof(tmp), stdin);
    if (tmp[0] != '\n') {
        tmp[strcspn(tmp, "\n")] = 0;
        strcpy(l->titre, tmp);
    }

    // Modification auteur
    printf("Modifier auteur (%s) : ", l->auteur);
    fgets(tmp, sizeof(tmp), stdin);
    if (tmp[0] != '\n') {
        tmp[strcspn(tmp, "\n")] = 0;
        strcpy(l->auteur, tmp);
    }

    // Modification catégorie
    printf("Modifier catégorie (%s) : ", l->categorie);
    fgets(tmp, sizeof(tmp), stdin);
    if (tmp[0] != '\n') {
        tmp[strcspn(tmp, "\n")] = 0;
        strcpy(l->categorie, tmp);
    }

    // Modification ISBN
    printf("Modifier ISBN (%s) : ", l->isbn);
    fgets(tmp, sizeof(tmp), stdin);
    if (tmp[0] != '\n') {
        tmp[strcspn(tmp, "\n")] = 0;
        strcpy(l->isbn, tmp);
    }

    // Modification année
    printf("Modifier année (%d) : ", l->annee);
    int annee;
    if (scanf("%d", &annee) == 1) {
        l->annee = annee;
        int c; while ((c=getchar())!='\n' && c!=EOF) {}
    }

    // Modification disponibilité
    printf("Modifier disponibilité (1=dispo, 0=emprunté) (%d) : ", l->disponible);
    int dispo;
    if (scanf("%d", &dispo) == 1) {
        l->disponible = dispo;
        int c; while ((c=getchar())!='\n' && c!=EOF) {}
    }

    printf("Livre modifié.\n");
}

// ---------------------------------------------------------
// Afficher tous les livres
// ---------------------------------------------------------
void afficherLivres(Livre *livres, int nbLivres) {
    if (nbLivres == 0) {
        printf("Aucun livre.\n");
        return;
    }
    for (int i = 0; i < nbLivres; i++) {
        printf("ID: %d | Titre: %s | Auteur: %s | Catégorie: %s | ISBN: %s | Année: %d | Disponible: %s\n",
               livres[i].id, livres[i].titre, livres[i].auteur,
               livres[i].categorie, livres[i].isbn, livres[i].annee,
               livres[i].disponible ? "Oui" : "Non");
    }
}

// Vérifie si un livre est disponible par ISBN
int LivreEstDisponible(Livre *livres, int nbLivres, const char *isbn){
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0)
            return livres[i].disponible;
    }
    return 0; // livre non trouvé → pas disponible
}

// ---------------------------------------------------------
// Recherche livre par titre exact (insensible à la casse)
// ---------------------------------------------------------
int rechercherLivre(Livre *livres, int nbLivres, char *titre) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcasecmp(livres[i].titre, titre) == 0)
            return i;
    }
    return -1; // non trouvé
}

// ---------------------------------------------------------
// Recherche livre par ISBN
// ---------------------------------------------------------
int rechercherLivreParISBN(Livre *livres, int nbLivres, char *isbn) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0)
            return i;
    }
    return -1; // non trouvé
}

// ---------------------------------------------------------
// Trier livres par titre (ordre alphabétique, insensible à la casse)
// ---------------------------------------------------------
void trierLivres(Livre *livres, int nbLivres) {
    for (int i = 0; i < nbLivres-1; i++) {
        for (int j = i+1; j < nbLivres; j++) {
            if (strcasecmp(livres[i].titre, livres[j].titre) > 0) {
                Livre tmp = livres[i];
                livres[i] = livres[j];
                livres[j] = tmp;
            }
        }
    }
}

// ---------------------------------------------------------
// Affichage interactif par titre
// ---------------------------------------------------------
void afficherLivreParTitre(Livre *livres, int nbLivres) {
    char titre[100];
    printf("Entrez le titre du livre à rechercher : ");
    fgets(titre, sizeof(titre), stdin);
    titre[strcspn(titre, "\n")] = 0;

    int idx = rechercherLivre(livres, nbLivres, titre);
    if (idx != -1) {
        Livre *l = &livres[idx];
        printf("ID: %d | Titre: %s | Auteur: %s | Catégorie: %s | ISBN: %s | Année: %d | Disponible: %s\n",
               l->id, l->titre, l->auteur, l->categorie, l->isbn, l->annee,
               l->disponible ? "Oui" : "Non");
    } else {
        printf("Livre non trouvé.\n");
    }
}

// ---------------------------------------------------------
// Recherche livre partielle (mot-clé dans le titre)
// ---------------------------------------------------------
void rechercherLivrePartiel(Livre *livres, int nbLivres) {
    char recherche[100];
    printf("Entrez un mot ou une partie du titre à rechercher : ");
    fgets(recherche, sizeof(recherche), stdin);
    recherche[strcspn(recherche, "\n")] = 0; // enlève le retour chariot

    int trouve = 0;
    for (int i = 0; i < nbLivres; i++) {
        if (strcasestr(livres[i].titre, recherche)) {  // recherche insensible à la casse
            printf("ID: %d | Titre: %s | Auteur: %s | Catégorie: %s | ISBN: %s | Année: %d | Disponible: %s\n",
                   livres[i].id, livres[i].titre, livres[i].auteur,
                   livres[i].categorie, livres[i].isbn, livres[i].annee,
                   livres[i].disponible ? "Oui" : "Non");
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun livre correspondant à '%s'.\n", recherche);
    }
}
