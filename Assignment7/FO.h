#include<stdio.h>

typedef struct DataNode {
	int mis;
	char name[10];
	char stream[10];
	double cgpa;
} DataNode;

void InsertRecord(char* fileName, DataNode data);
void Search(char* fileName, int mis);
void Delete(char* fileName, int mis);
void Display(char* fileName);
void DisplayStreamWise(char* fileName);

