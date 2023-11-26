/***********************************************BORAZ BOUCHANE VALLETTE SETTBON**************************************************************************/
/********************************PROJET théorie des graphes : optimisation d'une ligne d'assemblage groupe 91******************************************************/


#include <stdio.h>


int main(){
    printf("debut du projet\n");
    printf("commencement de la theorie des graphes\n");
    printf("premier commit de toute ma vie\n");

}


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
#include <limits.h>

#define V 9

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printSolution(int dist[]) {
    printf("Sommet \t Distance depuis la source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);

    return 0;
}

