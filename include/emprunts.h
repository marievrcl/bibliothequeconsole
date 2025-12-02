//
// Created by Marie Viricel on 02/12/2025.
//
#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "livres.h"
#include "utilisateurs.h"

#define F_EMPRUNTS DATA_DIR "/emprunts.txt"

typedef struct {
    int idLivre;
    int idUtilisateur;
    char dateEmprunt[20];
    char dateRetour[20];
} Emprunt;

// Déclaration uniquement de tes fonctions emprunt/retour, PAS de LivreEstDisponible
void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *utilisateurs, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts);

void retournerLivre(Livre *livres,Emprunt *emprunts, int nbEmprunts, int idLivre, const char *dateRetour);

void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);

void detecterRetards(int nbEmprunts, Emprunt *emprunts);

int calculerAmende(const char *dateE, const char *dateR);

void afficherAmendes(int nbEmprunts, Emprunt *emprunts);


#endif



