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