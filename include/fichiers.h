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

// Déclaration des fonctions pour gérer les fichiers de la bibliothèque

void chargerLivres(Livre *livres, int *nbLivres);
// Charge tous les livres depuis le fichier livres.txt dans le tableau livres
// Met à jour le nombre total de livres via nbLivres

void sauvegarderLivres(Livre *livres, int nbLivres);
// Sauvegarde tous les livres du tableau livres dans le fichier livres.txt
// nbLivres indique combien de livres doivent être sauvegardés

void chargerUtilisateurs(Utilisateur *users, int *nbUsers);
// Charge tous les utilisateurs depuis utilisateurs.txt dans le tableau users
// Met à jour le nombre total d'utilisateurs via nbUsers

void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers);
// Sauvegarde tous les utilisateurs du tableau users dans utilisateurs.txt
// nbUsers indique combien d'utilisateurs doivent être sauvegardés

void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);
// Charge tous les emprunts depuis emprunts.txt dans le tableau emprunts
// Met à jour le nombre total d'emprunts via nbEmprunts

void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts);
// Sauvegarde tous les emprunts du tableau emprunts dans emprunts.txt
// nbEmprunts indique combien d'emprunts doivent être sauvegardés

#endif
// Fin de la protection contre inclusion multiple (#ifndef ... #define ... #endif)


