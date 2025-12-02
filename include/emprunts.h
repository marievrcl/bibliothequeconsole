//
// Created by Marie Viricel on 02/12/2025.
//

#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "livres.h"
#include "utilisateurs.h"

#define MAX_EMPRUNTS 100

typedef struct {
    int idLivre;
    int idUtilisateur;
    char dateEmprunt[11];   // format "JJ/MM/AAAA"
    char dateRetour[11];    // format "JJ/MM/AAAA", vide si pas encore rendu
} Emprunt;

// Gestion des emprunts
void ajouterEmprunt(Emprunt emprunts[], int *nbEmprunts, int idLivre, int idUtilisateur, const char *dateEmprunt);
void retournerLivre(Emprunt emprunts[], int nbEmprunts, int idLivre, const char *dateRetour);
void afficherEmprunts(const Emprunt emprunts[], int nbEmprunts, const Livre livres[], int nbLivres, const Utilisateur utilisateurs[], int nbUtilisateurs);
void sauverEmprunts(const Emprunt emprunts[], int nbEmprunts);
void chargerEmprunts(Emprunt emprunts[], int *nbEmprunts);

// Nouvelles fonctions pour le menu
void emprunterLivre(Livre livres[], int nbLivres,
                    Utilisateur utilisateurs[], int nbUsers,
                    Emprunt emprunts[], int *nbEmprunts);
void verifierRetards(const Emprunt emprunts[], int nbEmprunts);


#endif


