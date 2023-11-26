//
// Created by boraz on 22/11/2023.
//

#include "header.h"

// Algorithme de Prim pour trouver un arbre couvrant minimal.
void prim(t_graphe* graphe, t_sommet** sommet, t_arc* arc,int sommet_initial)
{
    int min=5000;
    int nb_sommets_marque=0;
    int poids_total=0;
    int sommet_a_marquer=-1;
    for(int i=0;i<graphe->ordre;i++)
    {
        graphe->pSommet[i]->pre=-1;
        graphe->pSommet[i]->marque=0;
    }

    graphe->pSommet[sommet_initial]->marque=1;

    nb_sommets_marque+=1;

    do{
        min=5000;
        for(int i=0;i<graphe->ordre;i++)
        {
            if(graphe->pSommet[i]->marque==1)
            {
                t_arc* arc_tmp = graphe->pSommet[i]->arc;
                while(arc_tmp !=NULL)
                {
                    if(graphe->pSommet[arc_tmp->sommet]->marque==0)
                    {
                        if(arc_tmp->poids<min)
                        {
                            min=arc_tmp->poids;
                            sommet_a_marquer=arc_tmp->sommet;
                            graphe->pSommet[arc_tmp->sommet]->pre=graphe->pSommet[i]->valeur;

                        }
                    }
                    arc_tmp = arc_tmp->arc_suivant;
                }
            }
        }
        poids_total+=min;
        graphe->pSommet[sommet_a_marquer]->marque=1;
        nb_sommets_marque++;
    }while(nb_sommets_marque != graphe->ordre);

    //Affichage
    printf("\nL'arbre se presente sous la forme suivant : (Sommet de l'arbre) <-- (Son predeceseur dans l'arbre)\n\n");
    for(int i=0;i<graphe->ordre;i++)
    {
        if(graphe->pSommet[i]->valeur==sommet_initial)
        {
            printf("\t%d <-- sommet initial donc pas de predecesseur\n",graphe->pSommet[i]->valeur);
        }
        else
        {
            printf("\t%d <-- %d\n",graphe->pSommet[i]->valeur,graphe->pSommet[i]->pre);
        }

    }
    printf("\nLe poids total minimal est : %d\n\n", poids_total); //Affichage de
    printf("\nLe poids total minimal est : %d\n\n", poids_total); //Affichage de
}
///encore un commit
///x2


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // Nombre de sommets dans le graphe

// Fonction utilitaire pour trouver le sommet avec la clé minimale
int trouverMinimumCle(int cle[], int inclusDansArbre[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!inclusDansArbre[v] && cle[v] < min) {
            min = cle[v];
            min_index = v;
        }
    }

    return min_index;
}

// Fonction utilitaire pour afficher l'arbre couvrant minimum
void afficherArbreCouvrant(int parent[], int graphe[V][V]) {
    printf("Arête \t Poids\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t %d\n", parent[i], i, graphe[i][parent[i]]);
}

// Fonction principale implémentant l'algorithme de Prim pour un graphe donné
void prim(int graphe[V][V]) {
    int parent[V];  // Tableau pour stocker l'arbre couvrant minimum
    int cle[V];     // Tableau pour stocker les clés utilisées pour choisir le sommet avec la clé minimale
    int inclusDansArbre[V];  // Tableau pour indiquer si le sommet est inclus dans l'arbre couvrant minimum

    // Initialiser toutes les clés comme infini et marquer tous les sommets comme non inclus dans l'arbre
    for (int i = 0; i < V; i++) {
        cle[i] = INT_MAX;
        inclusDansArbre[i] = 0;
    }

    // La première clé est toujours 0, elle sera choisie en premier
    cle[0] = 0;
    parent[0] = -1;  // Le premier nœud est toujours la racine de l'arbre

    // Construire l'arbre couvrant minimum
    for (int count = 0; count < V - 1; count++) {
        // Choisir le sommet avec la clé minimale du set des sommets non encore inclus dans l'arbre
        int u = trouverMinimumCle(cle, inclusDansArbre);

        // Le sommet choisi est inclus dans l'arbre
        inclusDansArbre[u] = 1;

        // Mettre à jour les clés et les parents des sommets adjacents du sommet choisi
        for (int v = 0; v < V; v++) {
            // Mettre à jour cle[v] seulement si v n'est pas inclusDansArbre[v], il y a une arête de u à v,
            // et si le poids de l'arête de u à v est plus petit que la clé actuelle de v
            if (graphe[u][v] && !inclusDansArbre[v] && graphe[u][v] < cle[v]) {
                parent[v] = u;
                cle[v] = graphe[u][v];
            }
        }
    }

    // Afficher l'arbre couvrant minimum
    afficherArbreCouvrant(parent, graphe);
}

int main() {
    // Exemple de graphe pondéré (représentation matricielle d'adjacence)
    int graphe[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Appeler la fonction Prim
    prim(graphe);

    return 0;
}
