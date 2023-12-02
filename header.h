//
// Created by boraz on 26/11/2023.
//
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H

typedef struct Node_Workshop_Pointer
{
    struct node* nodes;
    struct WorkShop* WorkShops;
    int SizeNodeArray;
    int SizeWorkShopsArray;

} t_pointers;

typedef struct node
{
    int IdNumber;
    float operationTime;
    int* prevnode;
    int depthOperation;
    int Size_Of_Incompatibility_Array;
    int Size_Of_Previous_Array;
    int* inconmpatibility;
    int workshopAssigned;
} t_node;

typedef struct WorkShop
{
    /// FOR SIMULATION
    int CurrentOperation;
    long long OperationTimer;
    /// Data
    int identifier;
    float TotalTimeCycle;
    int SizeOfNamesArray;
    int* nodesNames;
    int SizeOfNodeIncompatibilityArray;
    int* nodesincompatibility;
} t_WorkShop;

t_node* readfileOperationFile(char FileName[], int* SizeOfOperation);
int** readfileexclusionsandlink(char FileName[],int* SizeOfExclusion);
void Free_Double_Array(int** Tab,int size);
void ReadArray(int** Tab,int size);
void InstallExclusionToStructur(t_node* nodes,int SizeOfNode);
int FindIndexOfIdName(int Name,t_node* nodes,int SizeOfArray);
void ReadNodes(t_node* nodes,int size);
void InstallPrecedenceToStructur(t_node* nodes,int SizeOfNode);
int IsWorkshopNotEmpty(t_WorkShop* Workshop,int SizeOfWorkshop);
t_WorkShop* SetupWorkshop(t_node* nodes,int SizeOfNode,int* SizeOfWorkshop);
t_WorkShop* WorkshopInnit(t_WorkShop* workshop,int size);
int PlaceNodeInWorkshop(t_WorkShop* WorkShops,int SizeOfTheWorkshop,int node);
int CanNodeBeInWorkshop(t_WorkShop Workshop,int node);
void UpdateWorkshopincompatibility(t_node* nodes,int node,t_WorkShop* Workshop);
void ReadWorkshop(t_WorkShop* WorkShops,int size,t_node* nodes);
long long current_time_in_ms();
int IsWorkShopDoneOperating(t_WorkShop Workshop,const int* OperationArray);
int FindOperationNotDone(t_WorkShop Workshop,const int* OperationArray,t_node* nodes);
void simulation(t_WorkShop* Workshop,int SizeOfWorkshop,t_node* nodes,int SizeOfOperatioon);
int canNodeBeProcessedWithPrecedence(const int* OperationArray,t_node* nodes,int node);
float readfileTimeCycle(char FileName[]);
int FindHeaviestWorkShop(t_WorkShop* Workshops,int SizeOfWorkShops);
void sortarray(int* Tab,int SizeOfTab);
int* GetNodePriority(t_WorkShop workshop);
int canNodeBeInWorkshop(t_WorkShop* workShop,int SizeOfWorkshop, int* excludedWorkshop,int SizeOfExlcludedWorkshop,int node,t_node* nodes, float cycleTimeMax);
int IsWorkShopExcluded(int actualWorkshop,const int* Tab, int sizeofTab);
t_WorkShop deletNodeFromWorkshop(t_WorkShop Workshop,int node);
t_WorkShop OrganisedArrayWorkshopName(t_WorkShop Workshop);
t_WorkShop* Verify_or_reorganise_WorkShops(t_WorkShop* WorkShop,int* SizeOfWorkshops,int* flag,int* LastNodeSwap,int* ListOfWorkShopTried,int* SizeOfWorkshopTried,t_node* nodes,int* lastWorkshop);
void freeNode(t_node* Nodes, int SizeofNodes);
void freeWorkShop(t_WorkShop* WorkShop, int SizeofWorkShop);
int IsWorkshopWithSingleNodePossible(t_WorkShop* Workshops,int SizeOfWorkshops,t_node* nodes,float MaxcycleTime);
void UpdateAllincompatibility(t_node* nodes,t_WorkShop* Workshop);
void verifWorkshop(t_WorkShop* Workshop,int SizeofWorkshop,int SizeOfNod);
float CalculMinimumTimeCycleforOperation(t_node* nodes, int pointer);
void goToXY( int col, int lig);
void LaunchWorkshopOrganizer(t_pointers* Organisation);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_06_91_HEADER_H














