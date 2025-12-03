//
// Created by Marie Viricel on 02/12/2025.
//

#ifndef BIBLIOTHEQUECONSOLE_LIVRES_H
#define BIBLIOTHEQUECONSOLE_LIVRES_H

#endif //BIBLIOTHEQUECONSOLE_LIVRES_H

//
// Module de gestion des livres : structure Livre et fonctions
// pour ajouter, afficher, modifier, supprimer, rechercher et trier.
//

#ifndef LIVRES_H
#define LIVRES_H

// Structure représentant un livre dans la bibliothèque
typedef struct {
    int  id;               // Identifiant unique du livre
    char titre[100];       // Titre du livre
    char auteur[100];      // Nom de l'auteur
    char categorie[50];    // Catégorie (roman, BD, etc.)
    char isbn[20];         // Code ISBN du livre
    int  annee;            // Année de publication
    int  disponible;       // 1 = disponible, 0 = emprunté
} Livre;

// === FONCTIONS DE GESTION DE LIVRES ===

// Ajoute un nouveau livre dans le tableau livres
// Incrémente nbLivres après insertion
void ajouterLivre(Livre *livres, int *nbLivres);

// Supprime un livre existant en utilisant son id
// Les livres suivants sont décalés pour combler le vide
void supprimerLivre(Livre *livres, int *nbLivres, int id);

// Modifie un livre existant (recherche par id)
// Permet de changer titre, auteur, catégorie, ISBN, année
void modifierLivre(Livre *livres, int nbLivres, int id);

// Affiche tous les livres sous forme de tableau lisible
void afficherLivres(Livre *livres, int nbLivres);

// Recherche un livre par titre exact
// Retourne l'index du livre dans le tableau ou -1 si introuvable
int rechercherLivre(Livre *livres, int nbLivres, char *titre);

// Recherche un livre par son ISBN exact
// Utilisé pour vérifier disponibilité ou emprunt
int rechercherLivreParISBN(Livre *livres, int nbLivres, char *isbn);

// Trie les livres par ordre alphabétique de titre
// Méthode simple par échange (bubble sort)
void trierLivres(Livre *livres, int nbLivres);

// Recherche un livre par mot ou partie du titre
// Affiche tous les livres correspondants
void rechercherLivrePartiel(Livre *livres, int nbLivres);

// Vérifie si un livre est disponible à partir de son ISBN
// Retourne 1 si disponible, 0 sinon
int LivreEstDisponible(Livre *livres, int nbLivres, const char *isbn);

#endif // LIVRES_H
// Fin de la protection contre inclusion multiple
