//
// Created by Marie Viricel on 02/12/2025.
//

//
// Created by Marie Viricel on 02/12/2025.
//

//
// Module de gestion des fichiers de données (dossier data/).
// Déclare les fonctions pour charger et sauvegarder les livres, utilisateurs et emprunts
// dans des fichiers texte (.txt) séparés.
//
#ifndef FICHIERS_H
#define FICHIERS_H

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

void chargerLivres(Livre *livres, int *nbLivres);
void sauvegarderLivres(Livre *livres, int nbLivres);

void chargerUtilisateurs(Utilisateur *users, int *nbUsers);
void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers);

void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);
void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts);

#endif

