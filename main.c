/***********************************************BORAZ BOUCHANE VALLETTE SETTBON**************************************************************************/
/********************************PROJET théorie des graphes : optimisation d'une ligne d'assemblage groupe 91******************************************************/


#include "header.h"

int main(){
    printf("debut du projet\n");
    printf("commencement de la theorie des graphes\n");
    printf("premier commit de toute ma vie\n");

}



// Fonction permettant de trier et de ranger dans l'ordre croissant les poids des différentes arêtes.
void tri_poids(t_graphe * graphe,t_arrete_temp Tablo_arretes[])
{
    t_arrete_temp tmp;// Création d'une variable temporaire de type t_arrete_temp
    int index;

    for (int i=0; i < (graphe->taille-1); i++)
    {
        index = i;

        for (int j=i + 1; j < graphe->taille; j++)
        {
            if (Tablo_arretes[index].poids > Tablo_arretes[j].poids)
                index = j;
        }

        if (index != i)
        {
            tmp = Tablo_arretes[i];
            Tablo_arretes[i] = Tablo_arretes[index];
            Tablo_arretes[index] = tmp;
        }
    }
}

int lire_pds(t_graphe* graphe, int num,int listearrete[],t_arrete_temp Tablo_arretes[],int num_arretes)
{
    int res=0,j=0,temp=0;// Initialisation des variables
    t_arc* arcc=graphe->pSommet[num]->arc;
    while(arcc!=NULL)
    {
        res=0;
        j=0;
        if(graphe->pSommet[num]->valeur>arcc->sommet)//different cas possible
        {
            temp=arcc-> sommet+ (10*graphe->pSommet[num]->valeur);
        }
        else
        {
            temp=graphe->pSommet[num]->valeur + (10*arcc->sommet);
        }

        for(int i=0;i<graphe->taille;i++)
        {
            if(listearrete[i]==temp)
            {
                res=1;
                break;
            }
            else
            {
                res=0;
            }
            if(listearrete[i]==0)
            {
                j=i;
            }
        }
        if(res==0)
        {
            Tablo_arretes[num_arretes].arrivee=arcc->sommet;//on place les differentes valeurs dans un tableau
            Tablo_arretes[num_arretes].depart=graphe->pSommet[num]->valeur;//on place les differentes valeurs dans un tableau
            Tablo_arretes[num_arretes].poids=arcc->poids;//on place les differentes valeurs dans un tableau
            listearrete[j]=temp;
            num_arretes++;
        }

        arcc=arcc->arc_suivant;
    }
    return num_arretes;
}

// Algorithme de Kruskal pour trouver un arbre couvrant minimal.


void tableau_a(t_arrete_temp *Tablo_arretes, t_graphe *graphe) {
    int num_arretes=0;// Initialisation du numéro d'arête à 0
    int listearretes[graphe->taille];// Tableau des arêtes de la taille de la taille du graphe
    for(int j=0;j<graphe->taille;j++)
    {
        listearretes[j]=0; // Attribution de la valeur 0 à chaque case du tableau
    }


    for(int i=0;i<graphe->ordre;i++)
    {
        num_arretes=lire_pds(graphe,i,listearretes,Tablo_arretes,num_arretes);
    }

    tri_poids(graphe,Tablo_arretes);
}


// Fonction permettant de créer un tableau de sommet pour Kruskal
void tableau_s(t_graphe * graphe,t_sommet_temp Tablo_sommets[]) {
    for (int i = 0; i < graphe->ordre; i++) {
        Tablo_sommets[i].comp_connex = i;
        Tablo_sommets[i].num_sommet = i;
    }
}



void Kruskal(t_graphe*  graphe)
{
    t_arrete_temp Tablo_arretes[graphe->taille]; // Initialisation du tableau des arêtes de la taille du graphe

    t_sommet_temp t_sommet_temp[graphe->ordre];// Initialisation du tableau des sommets de la taille de l'ordre du graphe
    int numencours=0,nbarete=0;
    int Poids_total=0;

    tableau_a(Tablo_arretes, graphe); // Appel de la fonction pour créer le tableau des arêtes
    tableau_s(graphe, t_sommet_temp);// Appel de la fonction pour créer le tableau des sommets


    while(numencours<graphe->ordre-1)
    {
        if(t_sommet_temp[Tablo_arretes[nbarete].depart].comp_connex!=t_sommet_temp[Tablo_arretes[nbarete].arrivee].comp_connex)
        {
            for(int k=0;k<graphe->ordre;k++)
            {
                if(t_sommet_temp[k].comp_connex==t_sommet_temp[Tablo_arretes[nbarete].arrivee].comp_connex && t_sommet_temp[k].num_sommet!=t_sommet_temp[Tablo_arretes[nbarete].arrivee].num_sommet)
                {
                    t_sommet_temp[k].comp_connex=t_sommet_temp[Tablo_arretes[nbarete].depart].comp_connex;
                }
            }
//Affichage 1
            t_sommet_temp[Tablo_arretes[nbarete].arrivee].comp_connex=t_sommet_temp[Tablo_arretes[nbarete].depart].comp_connex;
            printf("\nSommet de Depart  %d ---> Sommet d'Arrivee  %d ",t_sommet_temp[Tablo_arretes[nbarete].depart].num_sommet,t_sommet_temp[Tablo_arretes[nbarete].arrivee].num_sommet);
            Poids_total+=Tablo_arretes[nbarete].poids;
            numencours++;
        }
        nbarete++;
    }
//Affichage 2
    printf("\n\n");

    for(int j=0;j<graphe->ordre;j++)
    {
        printf("\n\tSommet : %d = composante connexe %d",t_sommet_temp[j].num_sommet,t_sommet_temp[j].comp_connex);
    }

    printf("\n\npoids total :  %d\n\n",Poids_total);


}





#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6  // Nombre de sommets dans le graphe

// Fonction pour trouver le sommet avec la distance minimale
int trouverMinDistance(int distance[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Fonction pour afficher le tableau des distances
void afficherSolution(int distance[]) {
    printf("Sommet \t Distance depuis le sommet source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, distance[i]);
}

// Fonction qui implémente l'algorithme de Dijkstra pour un graphe représenté par une matrice d'adjacence
void dijkstra(int graph[V][V], int src) {
    int distance[V];  // tableau pour stocker les distances les plus courtes depuis la source
    int sptSet[V];    // tableau pour indiquer si un sommet a déjà été inclus dans l'arbre des plus courts chemins

    // Initialiser toutes les distances comme infinies et aucun sommet n'a été inclus dans l'arbre des plus courts chemins
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // La distance de la source à elle-même est toujours 0
    distance[src] = 0;

    // Trouver le plus court chemin pour tous les sommets
    for (int count = 0; count < V - 1; count++) {
        // Choix du sommet ayant la plus petite distance non incluse dans l'arbre des plus courts chemins
        int u = trouverMinDistance(distance, sptSet);


Bien sûr ! Voici un exemple de code en C pour l'algorithme de Dijkstra. Cependant, il est important de noter que cet exemple suppose que le graphe est pondéré et représenté par une matrice d'adjacence.

```c
#include <stdio.h>
#include <limits.h>

#define V 6 // Nombre de sommets dans le graphe

// Fonction pour trouver le sommet avec la distance minimale
int trouverSommetMinimum(int distance[], int ensembleSommets[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (ensembleSommets[v] == 0 && distance[v] <= min)
        {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Fonction pour afficher la solution après l'exécution de l'algorithme de Dijkstra
void afficherSolution(int distance[])
{
    printf("Sommet \t Distance depuis le sommet source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, distance[i]);
}

// Fonction qui implémente l'algorithme de Dijkstra pour un graphe représenté par une matrice d'adjacence
void dijkstra(int graphe[V][V], int source)
{
    int distance[V]; // Tableau pour stocker les distances les plus courtes depuis la source jusqu'à chaque sommet
    int ensembleSommets[V]; // Tableau pour suivre les sommets inclus dans l'ensemble de sommets déjà traités

    // Initialisation des distances et de l'ensemble des sommets
    for (int i = 0; i < V; i++)
    {
        distance[i] = INT_MAX;
        ensembleSommets[i] = 0;
    }

    // La distance de la source vers elle-même est toujours 0
    distance[source] = 0;

    // Recherche de la plus courte distance pour tous les sommets
    for (int count = 0; count < V - 1; count++)
    {
        // Choix du sommet avec la distance minimale depuis l'ensemble des sommets encore non traités
        int u = trouverSommetMinimum(distance, ensembleSommets);

        // Marquer le sommet choisi comme traité
        ensembleSommets[u] = 1;

        // Mettre à jour la distance des sommets adjacents au sommet choisi
        for (int v = 0; v < V; v++)
        {
            if (!ensembleSommets[v] && graphe[u][v] && distance[u] != INT_MAX &&
                distance[u] + graphe[u][v] < distance[v])
            {
                distance[v] = distance[u] + graphe[u][v];
            }
        }
    }

    // Afficher la solution
    afficherSolution(distance);
}

int main()
{
    // Exemple de graphe pondéré représenté par une matrice d'adjacence
    int graphe[V][V] = {
        {0, 5, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 7, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 0}};

    // Appeler l'algorithme de Dijkstra avec le sommet source 0
    dijkstra(graphe, 0);

    return 0;
}
```

Dans cet exemple, le graphe est un graphe pondéré avec 6 sommets, représenté par une matrice d'adjacence. Vous pouvez adapter le code en fonction de votre graphe spécifique si vous en avez un différent.
        

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6  // Nombre de sommets dans le graphe

// Fonction utilitaire pour trouver le sommet avec la distance minimale
// parmi les sommets non encore inclus dans le plus court chemin calculé
int trouverMinimumDistance(int distance[], int inclusDansPlusCourtChemin[]) {
    int min = INT_MAX, min_index;




