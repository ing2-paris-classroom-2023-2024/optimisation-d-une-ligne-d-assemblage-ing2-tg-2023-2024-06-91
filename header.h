//
// Created by boraz on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H

#include <stdio.h>
#include <stdlib.h>

/// structures du graphe

typedef struct arc
{
    int sommet;
    int valeur;
    int poids;
    struct _arc* arc_suivant;
}t_arc;

typedef struct sommet
{
    t_arc* arc;
    int valeur;
    int marque;
    int pre;
    int dist;
    int degre;
}t_sommet;

typedef struct Graphe
{
    int taille;
    int ordre;
    t_sommet** pSommet;
}t_graphe;
typedef struct arrete_temp
{
    int depart;
    int arrivee;
    int poids;
}t_arrete_temp;

typedef struct sommet_temp
{
    int num_sommet;
    int comp_connex;
}t_sommet_temp;

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H
