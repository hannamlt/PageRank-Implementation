# PageRank-Implementation
Project Dauphine

README
   
# MidoRank

MidoRank est une implémentation personnalisée de l'algorithme PageRank, conçue pour analyser et classer les pages web en fonction de leur importance relative dans un réseau de liens.

## Fonctionnalités

- Analyse de fichiers contenant des informations sur les liens entre les pages
- Calcul des rangs des pages en utilisant une variante de l'algorithme PageRank
- Gestion efficace de la mémoire pour les structures de données complexes
- Utilisation d'une fonction de hachage pour optimiser certaines opérations

## Compilation

Pour compiler le projet, utilisez la commande suivante (assurez-vous d'avoir un Makefile approprié) :
make 


## Utilisation

Après la compilation, vous pouvez exécuter le programme avec la commande suivante :
./midorank [-t | -n] <fichier> <nombre_iterations>


Où :
- `-t` ou `-n` sont des options (à implémenter)
- `<fichier>` est le chemin vers le fichier contenant les informations sur les liens
- `<nombre_iterations>` est le nombre d'itérations pour l'algorithme MidoRank

## Structure du projet

- `srcs/links_utils.c` : Fonctions pour la gestion des liens
- `srcs/hash_utils.c` : Fonctions de hachage et utilitaires associés
- `srcs/main.c` : Point d'entrée du programme et logique principale
- `srcs/manage_memory.c` : Gestion de la mémoire
- `srcs/midorank.c` : Implémentation de l'algorithme MidoRank
- `srcs/page_utils.c` : Fonctions pour la gestion des pages
- `srcs/parse_file.c` : Analyse du fichier d'entrée



