/***********************************************BORAZ BOUCHANE VALLETTE SETTBON**************************************************************************/
/********************************PROJET théorie des graphes : optimisation d'une ligne d'assemblage groupe 91******************************************************/


#include "header.h"

// Size of array take all the array, so it's twice as big if each cell got 2 integer in it;

int main() {
    int FlagQuit = 0;
    int FirstTime = 1;
    char Buffer;
    t_pointers Organisation;
    Organisation.SizeWorkShopsArray = 0;
    Organisation.SizeNodeArray = 0;
    while(!FlagQuit)
    {
        int input;
        printf("What Action Would you performe \n1 : Launch \n2 : ShowWorkshop \n3 : ShowNodes \n4 : ShowPrecedence\n5 : Quit\n");
        fflush(stdin);
        scanf("%d",&input);
        switch (input) {
            case 1:
                goToXY(0,0);
                system("cls");
                if(!FirstTime)
                {
                    freeNode(Organisation.nodes,Organisation.SizeNodeArray);
                    freeWorkShop(Organisation.WorkShops,Organisation.SizeWorkShopsArray);
                }
                FirstTime = 0;
                LaunchWorkshopOrganizer(&Organisation);
                break;
            case 2:
                if(Organisation.SizeWorkShopsArray != 0)
                {
                    goToXY(0,0);
                    system("cls");
                    ReadWorkshop(Organisation.WorkShops,Organisation.SizeWorkShopsArray,Organisation.nodes);
                    printf("press enter to quit");
                    fflush(stdin);
                    scanf("%c",&Buffer);
                }
                else
                {
                    goToXY(0,0);
                    system("cls");
                    printf("WorkShop Not organized Yet ! please launch 1 First !");
                    Sleep(1000);
                }

                break;
            case 3:
                if(Organisation.SizeWorkShopsArray != 0)
                {
                    goToXY(0,0);
                    system("cls");
                    printf("Show nodes\n");
                    ReadNodes(Organisation.nodes,Organisation.SizeNodeArray);
                    printf("press enter to quit");
                    fflush(stdin);
                    scanf("%c",&Buffer);
                }
                else
                {
                    goToXY(0,0);
                    system("cls");
                    printf("WorkShop Not organized Yet ! please launch 1 First !");
                    Sleep(1000);
                }
                break;
            case 4:
                if(Organisation.SizeWorkShopsArray != 0)
                {
                    int flagStop = 0;
                    while(!flagStop)
                    {
                        goToXY(0,0);
                        system("cls");
                        int node;
                        printf("please input the node needed, type -999 to quit\n");
                        printf("Input Available : ");
                        for (int i = 0; i < Organisation.SizeNodeArray; ++i) {
                            printf("%d ",Organisation.nodes[i].IdNumber);
                        }
                        printf("\n");
                        fflush(stdin);
                        scanf("%d",&node);
                        if(node == -999)
                        {
                            break;
                        }
                        int pointer = FindIndexOfIdName(node,Organisation.nodes,Organisation.SizeNodeArray);
                        if(pointer == -1)
                        {
                            printf("Node doesn't existe please try again");
                            Sleep(1000);
                        }
                        else
                        {
                            system("cls");
                            goToXY(0,1);
                            int Iteration = 0;
                            printf("%d",node);
                            while(Organisation.nodes[pointer].Size_Of_Previous_Array !=0)
                            {
                                for (int i = 0; i < Organisation.nodes[pointer].Size_Of_Previous_Array; ++i) {
                                    if(i == 0)
                                    {
                                        goToXY(Iteration*6+3,i+1);
                                        printf("-->%d",Organisation.nodes[Organisation.nodes[pointer].prevnode[i]].IdNumber);
                                    }
                                    else
                                    {
                                        goToXY(Iteration*6+3,i+1);
                                        printf("\\->%d",Organisation.nodes[Organisation.nodes[pointer].prevnode[i]].IdNumber);
                                    }
                                }
                                Iteration++;
                                pointer = Organisation.nodes[pointer].prevnode[0];
                            }
                            printf("\n\n\npress enter to Continue");
                            fflush(stdin);
                            scanf("%c",&Buffer);
                        }
                    }
                }
                else
                {
                    goToXY(0,0);
                    system("cls");
                    printf("WorkShop Not organized Yet ! please launch 1 First !");
                    Sleep(1000);
                }
                break;
            case 5:
                printf("See you next time\n");
                FlagQuit = !FlagQuit;
                /// FREE MEMORY
                /// need better Free methode
                freeNode(Organisation.nodes,Organisation.SizeNodeArray);
                freeWorkShop(Organisation.WorkShops,Organisation.SizeWorkShopsArray);
                break;
            default:
                printf("input incorrect, please try again\n");
                break;
        }
        goToXY(0,0);
        system("cls");
    }
}

void LaunchWorkshopOrganizer(t_pointers* Organisation)
{
    int VerifTiming = 1;
    int LastNodeSwap = -1;
    int SizeOfWorkshopTried = 1;
    int* ListeOfWorkshopTried = NULL;
    int lastWorkshop;
    ListeOfWorkshopTried = (int*)realloc(ListeOfWorkshopTried,sizeof(int)*SizeOfWorkshopTried);
    ListeOfWorkshopTried[0] = -1;

    Organisation->nodes = readfileOperationFile("operations.txt",&Organisation->SizeNodeArray);
    InstallExclusionToStructur(Organisation->nodes,Organisation->SizeNodeArray);
    InstallPrecedenceToStructur(Organisation->nodes,Organisation->SizeNodeArray);
    Organisation->WorkShops = SetupWorkshop(Organisation->nodes,Organisation->SizeNodeArray,&Organisation->SizeWorkShopsArray);
    /// ReadNodes(nodes,SizeOfNodesArray);
    while(VerifTiming)
    {
        simulation(Organisation->WorkShops,Organisation->SizeWorkShopsArray,Organisation->nodes,Organisation->SizeNodeArray);
        Organisation->WorkShops = Verify_or_reorganise_WorkShops(Organisation->WorkShops,&Organisation->SizeWorkShopsArray,&VerifTiming,&LastNodeSwap,ListeOfWorkshopTried,&SizeOfWorkshopTried,Organisation->nodes,&lastWorkshop);
        printf("Last Swap : %d\nLast Workshop : %d\n\n",Organisation->nodes[LastNodeSwap].IdNumber,lastWorkshop);
        //ReadWorkshop(Organisation->WorkShops,Organisation->SizeWorkShopsArray,Organisation->nodes);
        verifWorkshop(Organisation->WorkShops,Organisation->SizeWorkShopsArray,Organisation->SizeNodeArray);
    }
    system("cls");
    goToXY(0,0);
    printf("DONE !");
    Sleep(1000);
}

void verifWorkshop(t_WorkShop* Workshop,int SizeofWorkshop,int SizeOfNod)
{
    int tab[SizeOfNod];
    for (int i = 0; i < SizeOfNod; ++i) {
        tab[i] = 0;
    }
    for (int i = 0; i < SizeofWorkshop; ++i) {
        for (int j = 0; j < Workshop[i].SizeOfNamesArray; ++j) {
            if(tab[Workshop[i].nodesNames[j]] == 0)
            {
                tab[Workshop[i].nodesNames[j]] = 1;
            }
            else
            {
                printf("An Error has occurred, Node in 2 Different Workshop\n");
                exit(-999);
            }
        }
    }
}

void freeNode(t_node* Nodes, int SizeofNodes)
{
    for (int i = 0; i < SizeofNodes; ++i) {
        free(Nodes[i].inconmpatibility);
        free(Nodes[i].prevnode);
    }
    free(Nodes);
}

void freeWorkShop(t_WorkShop* WorkShop, int SizeofWorkShop)
{
    for (int i = 0; i < SizeofWorkShop; ++i) {
        free(WorkShop[i].nodesNames);
        free(WorkShop[i].nodesincompatibility);
    }
    free(WorkShop);
}

void goToXY( int col, int lig)
{
    COORD mycoord;
    mycoord.X = (signed short)col;
    mycoord.Y = (signed short)lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void Free_Double_Array(int** Tab,int size){
    for(int i = 0 ; i < size; i++)
    {
        free(Tab[i]);
    }
    free(Tab);
    //printf("FreeArray Successfully\n");
}
/*
void ReadArray(int** Tab,int size){
    for(int i = 0 ; i < size; i++)
    {
        printf("%d %d\n",Tab[i][0],Tab[i][1]);
    }
}
*/
void ReadNodes(t_node* nodes,int size){
    for(int i = 0 ; i < size; i++)
    {
        printf("Node %d \n",nodes[i].IdNumber);
        printf("Operation Time : %f\n", nodes[i].operationTime);
        printf("Incompatibility : %d\n",nodes[i].Size_Of_Incompatibility_Array);
        for(int j = 0 ; j < nodes[i].Size_Of_Incompatibility_Array ; j ++)
        {
            printf("%d ",nodes[nodes[i].inconmpatibility[j]].IdNumber);
        }
        printf("\nPrevious node : %d\n",nodes[i].Size_Of_Previous_Array);
        for(int j = 0 ; j < nodes[i].Size_Of_Previous_Array ; j ++)
        {
            printf("%d ",nodes[nodes[i].prevnode[j]].IdNumber);
        }
        printf("\n\n");
    }
}

void ReadWorkshop(t_WorkShop* WorkShops,int size,t_node* nodes){
    for(int i = 0 ; i < size; i++)
    {
        printf("WorkShop %d \n",WorkShops[i].identifier);
        printf("Number of incompatible node : %d\n",WorkShops[i].SizeOfNodeIncompatibilityArray);
        for (int j = 0; j < WorkShops[i].SizeOfNodeIncompatibilityArray; ++j) {
            printf("%d ",nodes[WorkShops[i].nodesincompatibility[j]].IdNumber);
        }
        printf("\n");
        printf("Number of node : %d\n",WorkShops[i].SizeOfNamesArray );
        for (int j = 0; j < WorkShops[i].SizeOfNamesArray; ++j) {
            printf("%d ",nodes[WorkShops[i].nodesNames[j]].IdNumber);
        }
        printf("\n");
        /// Total cycle time
        printf("\n");
    }
}

int FindIndexOfIdName(int Name,t_node* nodes,int SizeOfArray)
{
    for(int i = 0 ; i < SizeOfArray;i++)
    {
        if(Name == nodes[i].IdNumber)
        {
            return i;
        }
    }
    return -1;
}

void InstallExclusionToStructur(t_node* nodes,int SizeOfNode){
    int SizeOfExclusion;
    int** exclusionArray = readfileexclusionsandlink("exclusion.txt",&SizeOfExclusion);
    ///innit nodesArray (no particular reason just so that it's done)
    for(int i = 0 ; i < SizeOfNode ; i++)
    {
        nodes[i].Size_Of_Incompatibility_Array = 0;
        nodes[i].inconmpatibility = NULL;
        nodes[i].prevnode = NULL;
        nodes[i].workshopAssigned = -1;
        nodes[i].Size_Of_Previous_Array = 0;
    }
    for(int i = 0 ; i < SizeOfExclusion ; i++)
    {
        int NodeA = FindIndexOfIdName(exclusionArray[i][0],nodes,SizeOfNode);
        int NodeB = FindIndexOfIdName(exclusionArray[i][1],nodes,SizeOfNode);
        if(NodeA == -1 || NodeB == -1){ printf("Exception: an operation didn't existe in the file Operation.txt");exit(-2);}
        nodes[NodeA].Size_Of_Incompatibility_Array++;
        nodes[NodeB].Size_Of_Incompatibility_Array++;
        nodes[NodeA].inconmpatibility = (int*) realloc(nodes[NodeA].inconmpatibility,sizeof(int)*nodes[NodeA].Size_Of_Incompatibility_Array);
        nodes[NodeB].inconmpatibility = (int*) realloc(nodes[NodeB].inconmpatibility,sizeof(int)*nodes[NodeB].Size_Of_Incompatibility_Array);
        nodes[NodeA].inconmpatibility[nodes[NodeA].Size_Of_Incompatibility_Array-1]=NodeB;
        nodes[NodeB].inconmpatibility[nodes[NodeB].Size_Of_Incompatibility_Array-1]=NodeA;
    }
    Free_Double_Array(exclusionArray,SizeOfExclusion);
}

void InstallPrecedenceToStructur(t_node* nodes,int SizeOfNode){
    int SizeOfPrecedence;
    int** PrecedenceArray = readfileexclusionsandlink("precedences.txt",&SizeOfPrecedence);
    for(int i = 0 ; i < SizeOfPrecedence ; i++)
    {
        int NodeA = FindIndexOfIdName(PrecedenceArray[i][0],nodes,SizeOfNode);
        int NodeB = FindIndexOfIdName(PrecedenceArray[i][1],nodes,SizeOfNode);
        if(NodeA == -1 || NodeB == -1){ printf("Exception: an operation didn't existe in the file Operation.txt");exit(-2);}
        nodes[NodeB].Size_Of_Previous_Array++;
        nodes[NodeB].prevnode = (int*) realloc(nodes[NodeB].prevnode,sizeof(int)*nodes[NodeB].Size_Of_Previous_Array);
        nodes[NodeB].prevnode[nodes[NodeB].Size_Of_Previous_Array-1]=NodeA;
    }
    Free_Double_Array(PrecedenceArray,SizeOfPrecedence);
}

t_WorkShop* SetupWorkshop(t_node* nodes,int SizeOfNode,int* SizeWorkshop)
{
    int SizeOfWorkshop = 1;
    t_WorkShop* Workshop = NULL;
    Workshop = WorkshopInnit(Workshop,SizeOfWorkshop);

    int* Task = (int*)calloc(SizeOfNode,sizeof(int));
    for(int i = 0 ; i < SizeOfNode;i++)
    {
        int Placement = PlaceNodeInWorkshop(Workshop,SizeOfWorkshop,i);
        /// CASE WHERE NODE CAN BE PLACED IN 1 WORKSHOP
        if(Placement!=-1)
        {
            Workshop[Placement].SizeOfNamesArray++;
            Workshop[Placement].nodesNames = (int*)realloc(Workshop[Placement].nodesNames,sizeof(int)*Workshop[Placement].SizeOfNamesArray);
            Workshop[Placement].nodesNames[Workshop[Placement].SizeOfNamesArray-1] = i;
            UpdateWorkshopincompatibility(nodes,i,&Workshop[Placement]);
        }
            /// CASE WHERE NODE CAN'T BE PLACED IN 1 WORKSHOP AND NEED TO CREATE A NEW ONE
        else
        {
            SizeOfWorkshop++;
            Workshop = WorkshopInnit(Workshop,SizeOfWorkshop);
            Workshop[SizeOfWorkshop-1].SizeOfNamesArray++;
            Workshop[SizeOfWorkshop-1].nodesNames = (int*)realloc(Workshop[SizeOfWorkshop-1].nodesNames,sizeof(int)*Workshop[SizeOfWorkshop-1].SizeOfNamesArray);
            Workshop[SizeOfWorkshop-1].nodesNames[Workshop[SizeOfWorkshop-1].SizeOfNamesArray-1] = i;
            UpdateWorkshopincompatibility(nodes,i,&Workshop[SizeOfWorkshop-1]);
        }
    }
    free(Task);
    *SizeWorkshop = SizeOfWorkshop;
    return Workshop;
}

float CalculMinimumTimeCycleforOperation(t_node* nodes, int pointer)
{
    float Time = (float)INT_MAX;
    for (int i = 0; i < nodes[pointer].Size_Of_Previous_Array; ++i) {
        float nextTIme =  CalculMinimumTimeCycleforOperation(nodes,nodes[pointer].prevnode[i]);
        if(nextTIme < Time)
        {
            Time = nextTIme;
        }
    }
    if(nodes[pointer].Size_Of_Previous_Array == 0)
    {
        return nodes[pointer].operationTime;
    }
    else
    {
        return nodes[pointer].operationTime + Time;
    }
}

int IsWorkshopWithSingleNodePossible(t_WorkShop* Workshops,int SizeOfWorkshops,t_node* nodes,float MaxcycleTime)
{
    int flagExistWorkshop = 0;
    for (int i = 0; i < SizeOfWorkshops; i++) {
        if(Workshops[i].SizeOfNamesArray != 1)
        {
            flagExistWorkshop = 1;
        }
        else
        {
            int pointeur = Workshops[i].nodesNames[0];
            float MinimumTimeCycle = CalculMinimumTimeCycleforOperation(nodes,pointeur);
            //printf("\nNODE : %d , TIMEFOUND : %f TIME MAX : %f\n",pointeur,MinimumTimeCycle,MaxcycleTime);
            if(MinimumTimeCycle > MaxcycleTime+0.00001)
            {
                return 1;
            }
        }
    }
    if(flagExistWorkshop)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

t_WorkShop* Verify_or_reorganise_WorkShops(t_WorkShop* WorkShop,int* SizeOfWorkshops,int* flag,int* LastNodeSwap,int* ListOfWorkShopTried,int* SizeOfWorkshopTried,t_node* nodes,int* lastWorkshop)
{
    float maxTiming = readfileTimeCycle("temps_cycle.txt");
    *flag = 0;
    for (int i = 0; i < *SizeOfWorkshops; ++i) {
        if(WorkShop[i].TotalTimeCycle > maxTiming)
        {
            *flag = 1;
            /* // THIS CODE ALLOW THE ENDING WHEN ONE ARRAY CONTAIN 1 Task and still exceed the time limit
            if(WorkShop[i].SizeOfNamesArray == 1)
            {
                printf("Can't Find Optimization for this TimeCycle");
                exit(4);
            }
            */
            if(IsWorkshopWithSingleNodePossible(WorkShop,*SizeOfWorkshops,nodes,maxTiming))
            {
                printf("Can't Find Optimization for this TimeCycle");
                exit(4);
            }
        }
    }
    if(*flag == 1)
    {
        int Lastpile0;
        int flagPile0equaltolast = 0;
        int heaviestWorkShops = FindHeaviestWorkShop(WorkShop,*SizeOfWorkshops);
        int* pile= GetNodePriority(WorkShop[heaviestWorkShops]);
        if(nodes[pile[0]].operationTime == nodes[*LastNodeSwap].operationTime)
        {
            Lastpile0 = pile[0];
            flagPile0equaltolast = 1;
            pile[0] = *LastNodeSwap;
        }
        for (int i = 0; i < WorkShop[heaviestWorkShops].SizeOfNamesArray; ++i) {
            if(pile[i] == *LastNodeSwap)
            {
                int WorkShopToSwap = canNodeBeInWorkshop(WorkShop,*SizeOfWorkshops,ListOfWorkShopTried,*SizeOfWorkshopTried,pile[i],nodes,maxTiming);
                if(WorkShopToSwap != -1)
                {
                    *SizeOfWorkshopTried +=1;
                    (int*)realloc(ListOfWorkShopTried,sizeof(int)*(*SizeOfWorkshopTried));
                    ListOfWorkShopTried[*SizeOfWorkshopTried-1] = WorkShopToSwap;
                    if(flagPile0equaltolast && i == 0)
                    {
                        WorkShop[*lastWorkshop] = deletNodeFromWorkshop(WorkShop[*lastWorkshop],Lastpile0);
                        //printf("TEST2, %d, %d\n",WorkShop[0].identifier,flagPile0equaltolast);
                        WorkShop[*lastWorkshop] = OrganisedArrayWorkshopName(WorkShop[*lastWorkshop]);
                        WorkShop[*lastWorkshop].SizeOfNamesArray--;
                        WorkShop[WorkShopToSwap].SizeOfNamesArray++;
                        WorkShop[WorkShopToSwap].nodesNames = (int*)realloc(WorkShop[WorkShopToSwap].nodesNames,sizeof(int)*WorkShop[WorkShopToSwap].SizeOfNamesArray);
                        WorkShop[WorkShopToSwap].nodesNames[WorkShop[WorkShopToSwap].SizeOfNamesArray-1] = pile[i];
                        *LastNodeSwap = pile[i];
                        UpdateAllincompatibility(nodes,&WorkShop[*lastWorkshop]);
                        UpdateWorkshopincompatibility(nodes,pile[i],&WorkShop[WorkShopToSwap]);
                        free(pile);
                        return WorkShop;
                    }
                    else
                    {
                        WorkShop[heaviestWorkShops] = deletNodeFromWorkshop(WorkShop[heaviestWorkShops],pile[i]);
                        //printf("TEST2, %d, %d\n",WorkShop[0].identifier,flagPile0equaltolast);
                        WorkShop[heaviestWorkShops] = OrganisedArrayWorkshopName(WorkShop[heaviestWorkShops]);
                        WorkShop[heaviestWorkShops].SizeOfNamesArray--;
                        WorkShop[WorkShopToSwap].SizeOfNamesArray++;
                        WorkShop[WorkShopToSwap].nodesNames = (int*)realloc(WorkShop[WorkShopToSwap].nodesNames,sizeof(int)*WorkShop[WorkShopToSwap].SizeOfNamesArray);
                        WorkShop[WorkShopToSwap].nodesNames[WorkShop[WorkShopToSwap].SizeOfNamesArray-1] = pile[i];
                        *LastNodeSwap = pile[i];
                        UpdateAllincompatibility(nodes,&WorkShop[heaviestWorkShops]);
                        UpdateWorkshopincompatibility(nodes,pile[i],&WorkShop[WorkShopToSwap]);
                        free(pile);
                        return WorkShop;
                    }
                }
                else
                {
                    //printf("SmthIsWrong\n");
                }
            }
            else
            {
                if(flagPile0equaltolast)
                {
                    pile[0] = Lastpile0;
                }
                *SizeOfWorkshopTried = 1;
                (int*)realloc(ListOfWorkShopTried,sizeof(int)*(*SizeOfWorkshopTried));
                ListOfWorkShopTried[0] = heaviestWorkShops;
                int WorkShopToSwap = canNodeBeInWorkshop(WorkShop,*SizeOfWorkshops,ListOfWorkShopTried,1,pile[i],nodes,maxTiming);
                if(WorkShopToSwap != -1)
                {
                    *SizeOfWorkshopTried = 2;
                    (int*)realloc(ListOfWorkShopTried,sizeof(int)*(*SizeOfWorkshopTried));
                    ListOfWorkShopTried[1] = WorkShopToSwap;
                    WorkShop[heaviestWorkShops] = deletNodeFromWorkshop(WorkShop[heaviestWorkShops],pile[i]);
                    //printf("TEST1\n");
                    //printf("%d\n",pile[i]);
                    WorkShop[heaviestWorkShops] = OrganisedArrayWorkshopName(WorkShop[heaviestWorkShops]);
                    WorkShop[heaviestWorkShops].SizeOfNamesArray--;
                    WorkShop[WorkShopToSwap].SizeOfNamesArray++;
                    WorkShop[WorkShopToSwap].nodesNames = (int*)realloc(WorkShop[WorkShopToSwap].nodesNames,sizeof(int)*WorkShop[WorkShopToSwap].SizeOfNamesArray);
                    WorkShop[WorkShopToSwap].nodesNames[WorkShop[WorkShopToSwap].SizeOfNamesArray-1] = pile[i];
                    *LastNodeSwap = pile[i];
                    *lastWorkshop = WorkShopToSwap;
                    UpdateAllincompatibility(nodes,&WorkShop[heaviestWorkShops]);
                    UpdateWorkshopincompatibility(nodes,pile[i],&WorkShop[WorkShopToSwap]);
                    free(pile);
                    return WorkShop;
                }
                else
                {
                    //printf("SmthIsWrong\n");
                }
            }
        }
        /// cas ou il il faut le mettre dans un autre array

        WorkShop[heaviestWorkShops] = deletNodeFromWorkshop(WorkShop[heaviestWorkShops],pile[0]);
        WorkShop[heaviestWorkShops] = OrganisedArrayWorkshopName(WorkShop[heaviestWorkShops]);
        WorkShop[heaviestWorkShops].SizeOfNamesArray--;
        (*SizeOfWorkshops) += 1;
        //printf("test 3 \n");
        WorkShop = WorkshopInnit(WorkShop,*SizeOfWorkshops);
        //printf("Test 3 : %d",WorkShop[2].identifier);
        WorkShop[*SizeOfWorkshops-1].SizeOfNamesArray = 1;
        WorkShop[*SizeOfWorkshops-1].nodesNames =(int*) realloc(WorkShop[*SizeOfWorkshops-1].nodesNames,sizeof(int)*WorkShop[*SizeOfWorkshops-1].SizeOfNamesArray);
        WorkShop[*SizeOfWorkshops-1].nodesNames[WorkShop[*SizeOfWorkshops-1].SizeOfNamesArray-1] = pile[0];
        *LastNodeSwap = pile[0];
        *lastWorkshop = (*SizeOfWorkshops)-1;
        UpdateAllincompatibility(nodes,&WorkShop[heaviestWorkShops]);
        UpdateWorkshopincompatibility(nodes,pile[0],&WorkShop[*SizeOfWorkshops-1]);
        free(pile);
        return WorkShop;
    }
    return WorkShop;
}

t_WorkShop deletNodeFromWorkshop(t_WorkShop Workshop,int node)
{
    for (int i = 0; i < Workshop.SizeOfNamesArray; ++i) {
        if(Workshop.nodesNames[i] == node)
        {
            Workshop.nodesNames[i] = -1;
        }
    }
    return Workshop;
}

t_WorkShop OrganisedArrayWorkshopName(t_WorkShop Workshop)
{
    int flag = 0;
    for (int i = 0; i < Workshop.SizeOfNamesArray; ++i) {
        if(flag == 0)
        {
            if(Workshop.nodesNames[i] == -1)
            {
                Workshop.nodesNames[i] = Workshop.nodesNames[i+1];
                flag = 1;
            }
        }
        else
        {
            Workshop.nodesNames[i] = Workshop.nodesNames[i+1];
        }
    }
    return Workshop;
}

int canNodeBeInWorkshop(t_WorkShop* workShop,int SizeOfWorkshop, int* excludedWorkshop,int SizeOfExlcludedWorkshop,int node,t_node* nodes, float cycleTimeMax)
{
    for (int i = 0; i < SizeOfWorkshop; ++i) {
        if(IsWorkShopExcluded(i,excludedWorkshop,SizeOfExlcludedWorkshop))
        {
            int compatible = 1;
            for (int j = 0; j < workShop[i].SizeOfNodeIncompatibilityArray; ++j) {
                if(workShop[i].nodesincompatibility[j] == node)
                {
                    compatible = 0;
                }
            }

            if(workShop[i].TotalTimeCycle + nodes[node].operationTime > cycleTimeMax)
            {
                compatible = 0;
            }

            if(compatible == 1)
            {
                return i;
            }
        }
    }
    return-1;
}

int IsWorkShopExcluded(int actualWorkshop,const int* Tab, int sizeofTab)
{
    for (int i = 0; i < sizeofTab; ++i) {
        if(actualWorkshop == Tab[i])
        {
            return 0;
        }
    }
    return 1;
}

int* GetNodePriority(t_WorkShop workshop)
{
    int* Tab = NULL;
    for (int i = 0; i < workshop.SizeOfNamesArray; ++i) {
        Tab = (int*)realloc(Tab,(i+1)*sizeof(int));
        Tab[i] = workshop.nodesNames[i];
        sortarray(Tab,(i+1));
    }
    return Tab;
}

void sortarray(int* Tab,int SizeOfTab)
{
    for (int i = SizeOfTab-1; i > 0; i--) {
        if(Tab[i] > Tab[i-1])
        {
            int buffer = Tab[i];
            Tab[i] = Tab[i-1];
            Tab[i-1] = buffer;
        }
    }
}

int FindHeaviestWorkShop(t_WorkShop* Workshops,int SizeOfWorkShops)
{
    float PrevTime = 0;
    int WS = 0;
    for (int i = 0; i < SizeOfWorkShops; ++i) {
        if(Workshops[i].TotalTimeCycle > PrevTime && Workshops[i].SizeOfNamesArray != 1)
        {
            PrevTime = Workshops[i].TotalTimeCycle;
            WS = i;
        }
    }
    return WS;
}

void UpdateAllincompatibility(t_node* nodes,t_WorkShop* Workshop)
{
    Workshop->SizeOfNodeIncompatibilityArray = 0;
    free(Workshop->nodesincompatibility);
    Workshop->nodesincompatibility = NULL;
    for (int i = 0; i < Workshop->SizeOfNamesArray; ++i) {
        UpdateWorkshopincompatibility(nodes,Workshop->nodesNames[i],Workshop);
    }
}

void UpdateWorkshopincompatibility(t_node* nodes,int node,t_WorkShop* Workshop)
{
    int flagAlreadyExiste;
    for(int i = 0 ; i < nodes[node].Size_Of_Incompatibility_Array ; i++)
    {
        flagAlreadyExiste = 0;
        for(int j = 0 ; j < Workshop->SizeOfNodeIncompatibilityArray ; j++)
        {
            if(nodes[node].inconmpatibility[i] == Workshop->nodesincompatibility[j])
            {
                flagAlreadyExiste = 1;
            }
        }
        if (flagAlreadyExiste == 0)
        {
            Workshop->SizeOfNodeIncompatibilityArray++;
            Workshop->nodesincompatibility = (int*) realloc(Workshop->nodesincompatibility,sizeof(int)*Workshop->SizeOfNodeIncompatibilityArray);
            Workshop->nodesincompatibility[Workshop->SizeOfNodeIncompatibilityArray-1] = nodes[node].inconmpatibility[i];
        }
    }
}

t_WorkShop* WorkshopInnit(t_WorkShop* workshop,int size)
{
    //printf("Size : %d\n",size);
    workshop = (t_WorkShop*)realloc(workshop,sizeof(t_WorkShop)*size);
    workshop[size-1].TotalTimeCycle = 0;
    workshop[size-1].identifier = size;
    workshop[size-1].nodesNames = NULL;
    workshop[size-1].nodesincompatibility = NULL;
    workshop[size-1].SizeOfNamesArray = 0;
    workshop[size-1].SizeOfNodeIncompatibilityArray = 0;
    return workshop;
}

int PlaceNodeInWorkshop(t_WorkShop* WorkShops,int SizeOfTheWorkshop,int node)
{
    for(int i = 0; i < SizeOfTheWorkshop ; i++) {
        if(CanNodeBeInWorkshop(WorkShops[i],node))
        {
            return i;
        }
    }
    return -1;
}

int CanNodeBeInWorkshop(t_WorkShop Workshop,int node)
{
    for (int i = 0; i < Workshop.SizeOfNodeIncompatibilityArray; ++i) {
        if(Workshop.nodesincompatibility[i] == node)
        {
            return 0;
        }
    }
    return 1;
}

long long current_time_in_ms() {
    struct timeval te;
    gettimeofday(&te, NULL);

    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // Calculate milliseconds
    return milliseconds;
}

void simulation(t_WorkShop* Workshop,int SizeOfWorkshop,t_node* nodes,int SizeOfOperatioon)
{
    printf("Launching Simulation ...\n\n");
    for (int i = 0; i < SizeOfWorkshop; ++i) {
        Workshop[i].TotalTimeCycle = 0;
    }
    int* WorkShopOccupation = (int*)calloc(SizeOfWorkshop,sizeof(int)); /// State of occupation of the array, 1 = occupied 0 =  not occupied
    int* OperationDone = (int*)calloc(SizeOfOperatioon,sizeof(int)); /// State of operation 0 = not done, 1 = done
    long long TimeStart = current_time_in_ms(); /// get time for final calculation ;
    while(IsWorkshopNotEmpty(Workshop,SizeOfWorkshop))
    {
        for (int i = 0; i < SizeOfWorkshop; ++i) {
            if(Workshop[i].TotalTimeCycle == 0) /// not finished to do simulation
            {
                if(WorkShopOccupation[i] == 0) /// if workshop isn't done,
                {
                    Workshop[i].CurrentOperation = FindOperationNotDone(Workshop[i],OperationDone,nodes);
                    if(Workshop[i].CurrentOperation != -1)
                    {
                        Workshop[i].OperationTimer = current_time_in_ms()+(long long)(nodes[Workshop[i].CurrentOperation].operationTime*1000);
                        /// printf("%d %d %lld %lld\n",i,Workshop[i].CurrentOperation+1,Workshop[i].OperationTimer,current_time_in_ms()); /// DEBUG TiMING;
                        WorkShopOccupation[i] = 1;
                    }
                }
                else
                {
                    if(Workshop[i].OperationTimer <= current_time_in_ms())
                    {
                        OperationDone[Workshop[i].CurrentOperation] = 1;
                        WorkShopOccupation[i] = 0;
                        if(IsWorkShopDoneOperating(Workshop[i],OperationDone))
                        {
                            Workshop[i].TotalTimeCycle = (float)(current_time_in_ms()-TimeStart)/1000;
                        }
                    }
                }
            }
        }
    }
    system("cls");
    goToXY(0,0);
    for (int i = 0; i < SizeOfWorkshop; ++i) {
        printf("TIME CYCLE WORKSHOP %d : %f \n",i,Workshop[i].TotalTimeCycle);
    }
    printf("\n\n");
    free(OperationDone);
    free(WorkShopOccupation);
}

int FindOperationNotDone(t_WorkShop Workshop,const int* OperationArray,t_node* nodes)
{
    for (int i = 0; i < Workshop.SizeOfNamesArray; ++i) {
        if(OperationArray[Workshop.nodesNames[i]] == 0)
        {
            if(canNodeBeProcessedWithPrecedence(OperationArray,nodes,Workshop.nodesNames[i]))
            {
                return Workshop.nodesNames[i];
            }
        }
    }
    return -1;
}

int canNodeBeProcessedWithPrecedence(const int* OperationArray,t_node* nodes,int node)
{
    for (int i = 0; i < nodes[node].Size_Of_Previous_Array; ++i) {
        if(OperationArray[nodes[node].prevnode[i]] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int IsWorkShopDoneOperating(t_WorkShop Workshop,const int* OperationArray)
{
    for (int i = 0; i < Workshop.SizeOfNamesArray; ++i) {
        if(OperationArray[Workshop.nodesNames[i]] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int IsWorkshopNotEmpty(t_WorkShop* Workshop,int SizeOfWorkshop){
    for(int i = 0 ; i < SizeOfWorkshop ; i ++)
    {
        if(Workshop[i].TotalTimeCycle == 0)
        {
            return 1;
        }
    }
    return 0;
}



