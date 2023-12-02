//
// Created by boraz on 22/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int** readfileexclusionsandlink(char FileName[],int* SizeOfExclusion){
    int size = 0;
    int num1,num2;
    int** Tab = NULL;
    FILE* FIle;
    FIle = fopen(FileName, "r");
    if (FIle == NULL) {
        perror("Error opening the file");
        exit(-1);
    }
    while (fscanf(FIle, "%d %d", &num1,&num2) == 2) {
        size++;
        Tab = (int**)realloc(Tab,sizeof(int*)*size);
        int* Cell = (int*)malloc(2*sizeof(int));
        Tab[size-1] = Cell;
        Tab[size-1][0] = num1;
        Tab[size-1][1] = num2;
    }
    *SizeOfExclusion = size;
    fclose(FIle);
    return Tab;
}

t_node* readfileOperationFile(char FileName[], int* SizeOfOperation){
    t_node* nodes = NULL;
    int size = 0;
    int num1;
    float num2;
    FILE* FIle;
    FIle = fopen(FileName, "r");
    if (FIle == NULL) {
        perror("Error opening the file");
        exit(-1);
    }
    while (fscanf(FIle, "%d %f", &num1,&num2) == 2) {
        size++;
        nodes = (t_node*)realloc(nodes,sizeof(t_node)*size);
        nodes[size-1].IdNumber = num1;
        nodes[size-1].operationTime = num2;
    }
    *SizeOfOperation = size;
    fclose(FIle);
    return nodes;
}

float readfileTimeCycle(char FileName[]){
    FILE* FIle;
    float num1;
    FIle = fopen(FileName, "r");
    if (FIle == NULL) {
        perror("Error opening the file");
        exit(-1);
    }
    fscanf(FIle, "%f", &num1);
    fclose(FIle);
    return num1;
}

