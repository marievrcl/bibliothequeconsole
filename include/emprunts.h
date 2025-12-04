//
// Created by Marie Viricel on 02/12/2025.
//
//
// Created by Marie Viricel on 02/12/2025.
//
//
// Created by Marie Viricel on 02/12/2025.
//
//
// Created by Marie Viricel on 02/12/2025.
//
#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "livres.h"
#include "utilisateurs.h"

#define F_EMPRUNTS DATA_DIR "/emprunts.txt"
// Définit le chemin complet du fichier des emprunts en utilisant le répertoire DATA_DIR

typedef struct {
    char isbn[20];          // ISBN du livre emprunté
    int idUtilisateur;      // ID de l'utilisateur qui a emprunté
    char dateEmprunt[20];   // Date de l'emprunt (format texte)
    char dateRetour[20];    // Date de retour (prévue ou réelle)
} Emprunt;                  // Structure représentant un emprunt

// Déclaration uniquement des fonctions relatives aux emprunts/retours
// Pas de fonction LivreEstDisponible ici

void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *utilisateurs, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts);
// Fonction qui gère l'emprunt d'un livre par un utilisateur

void retournerLivre(Livre *livres, Emprunt *emprunts, int nbEmprunts, int nbLivres);
// Fonction qui gère le retour d'un livre et met à jour l'état de disponibilité

void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);
// Charge les emprunts depuis le fichier F_EMPRUNTS dans le tableau en mémoire

void detecterRetards(int nbEmprunts, Emprunt *emprunts);
// Analyse les emprunts pour détecter ceux dont la date de retour est dépassée

float calculerAmende(const char *dateE, const char *dateR);
// Calcule l'amende en fonction de la date d'emprunt et de la date de retour

void afficherAmendes(int nbEmprunts, Emprunt *emprunts);
// Affiche les amendes pour tous les emprunts en retard

#endif
// Fin du fichier d'en-tête, protection contre inclusion multiple








