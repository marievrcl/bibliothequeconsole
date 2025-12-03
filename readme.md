# Projet ALGO C ING3

## RÉSUMÉ – Quel est le contexte et la problématique du projet ?
Le projet a été réalisé sur 7 semaines dans le cadre des cours de bases de données et de programmation en C. L’objectif était de mettre en pratique les compétences acquises et de développer notre autonomie. La problématique principale était de créer une bibliothèque numérique capable de gérer efficacement les livres, les utilisateurs et les emprunts, tout en permettant de sauvegarder et de charger les données facilement.

## Quels sont les objectifs techniques ?
Sur le plan technique, il s'agissait de concevoir un modèle relationnel avec MCD et MLD, de développer une application C modulaire en manipulant structures, pointeurs et fichiers, et de gérer toutes les entités du système. L’équipe a aussi ajouté des fonctionnalités avancées, comme des statistiques sur les emprunts, pour rendre l’application plus complète. Pour le développement, CLion a été utilisé pour le code et MySQL pour la base de données.

## Structure du projet

```
bibliothequeconsole/
│── CMakeLists.txt
│── README.md
│
├── include/
│   ├── livres.h
│   ├── utilisateurs.h
│   ├── emprunts.h
│   ├── fichiers.h
│   ├── stats.h
│   └── utils.h
│
├── src/
│   ├── main.c
│   ├── livres.c
│   ├── utilisateurs.c
│   ├── emprunts.c
│   ├── fichiers.c
│   ├── stats.c
│   └── utils.c
│
└── data/
    ├── livres.txt
    ├── utilisateurs.txt
    └── emprunts.txt
```


include/ → contient tous les fichiers .h (déclarations, structures, prototypes)

src/ → contient les implémentations .c

data/ → contient les fichiers textes

## Fonctionnalités principales

### Gestion des utilisateurs

- Ajouter un utilisateur 
- Modifier / supprimer 
- Consulter la liste 
- Gestion du quota d’emprunts

### Gestion des livres

- Ajouter / supprimer / modifier un livre 
- Recherche par ISBN 
- Mise à jour de la disponibilité

### Gestion des emprunts

- Enregistrer un emprunt 
- Enregistrer un retour 
- Détection des retards 
- Calcul automatique d’une amende

### Statistiques

- Nombre total d’emprunts 
- Top emprunteurs 
- Livres les plus empruntés 
- Taux d’utilisation

### Fonction recherche 
- Pouvoir rechercher un livre via son titre et afficher ses informations 

### Calculer Amende 
- Pouvoir calculer et affciher une amende dans le cas d'un retard de retour de livre

## Améliorations futures

- Interface graphique complète 
- Passage à une vraie base SQL 
- Authentification utilisateur

## Auteurs 
### Marie VIRICEL
### Eloise PIERRON
### James FOTSO