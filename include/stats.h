//
// Created by Marie Viricel on 02/12/2025.
//

#ifndef BIBLIOTHEQUECONSOLE_STATS_H
#define BIBLIOTHEQUECONSOLE_STATS_H

#endif //BIBLIOTHEQUECONSOLE_STATS_H

//
// Module de statistiques : fonctions pour afficher des informations globales
// sur la bibliothèque (nombre, disponibilité, top emprunts, utilisateur le plus actif).
//

#ifndef STATS_H
#define STATS_H

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

/**
 * Affiche un récapitulatif des statistiques générales de la bibliothèque
 * Inclut :
 * - le nombre total de livres, d'utilisateurs et d'emprunts
 * - le taux de disponibilité des livres
 * - l'utilisateur le plus actif (ayant emprunté le plus)
 * - le livre le plus emprunté
 */
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres);

/**
 * Analyse les emprunts et affiche le ou les livres les plus empruntés.
 * Utilise le tableau d'emprunts pour compter combien de fois chaque livre a été emprunté.
 */
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts,
                            Livre *livres, int nbLivres);

/**
 * Analyse les emprunts et affiche l'utilisateur le plus actif.
 * L'utilisateur le plus actif est celui qui a effectué le plus d'emprunts.
 */
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers);

#endif // STATS_H
// Fin de la protection contre inclusion multiple
