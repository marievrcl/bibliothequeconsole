//
// Created by Marie Viricel on 02/12/2025.
//

#ifndef BIBLIOTHEQUE_UTIL_H
#define BIBLIOTHEQUE_UTIL_H

#endif //BIBLIOTHEQUE_UTIL_H

#ifndef UTIL_H
#define UTIL_H

// Lit une ligne depuis l'entrée standard (stdin) et supprime les retours à la ligne (\n et \r)
void lireLigne(char *buf, int n);

// Remplit le buffer avec la date actuelle au format "JJ/MM/AAAA"
void dateAuj(char *buf);

// Calcule le nombre de jours écoulés depuis une date donnée au format "JJ/MM/AAAA"
// Renvoie un entier représentant le nombre de jours
int joursDepuis(const char *date); /* JJ/MM/AAAA -> jours écoulés depuis cette date */

#endif // UTIL_H
// Fin de la protection contre inclusion multiple
