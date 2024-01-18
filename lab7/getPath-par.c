#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "Workers.h"

int startVertex = 0;
int destinationVertex = 5;

int N=10;
int printLevel;
int numVertices = 10;
int numEdges = 30;
int graphDefault[][2] = { { 0, 1 }, { 0, 4 }, { 0, 5 }, { 1, 0 }, { 1, 2 }, { 1, 6 }, { 2, 1 }, { 2, 3 }, { 2, 7 },
		{ 3, 2 }, { 3, 4 }, { 3, 8 }, { 4, 0 }, { 4, 3 }, { 4, 9 }, { 5, 0 }, { 5, 7 }, { 5, 8 }, { 6, 1 },
		{ 6, 8 }, { 6, 9 }, { 7, 2 }, { 7, 5 }, { 7, 9 }, { 8, 3 }, { 8, 5 }, { 8, 6 }, { 9, 4 }, { 9, 6 },
		{ 9, 7 } };
int **graph;

typedef struct my_struct {
	int start;
	int end; 
}my_struct;


void initDefaultGraph() {
	graph = (int**)malloc(sizeof(int*)*numEdges);
	for(int i = 0; i < numEdges; i++) {
		graph[i] = (int*)malloc(sizeof(int)*2);
		graph[i][0] = graphDefault[i][0];
		graph[i][1] = graphDefault[i][1];
	}
}

void generateGraph(int nVertices, int nEdges)
 {
	srand(42);
	numVertices = nVertices;
	numEdges = nEdges;
	graph = (int**)malloc(sizeof(int*)*numEdges);
	for(int i = 0; i < numEdges; i++) {
		graph[i] = (int*)malloc(sizeof(int)*2);
		graph[i][0] = rand()%numVertices;
		graph[i][1] = rand()%numVertices;
		if(graph[i][0] == graph[i][1])
			i--;
	}
}

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

 
void printAll(int * v, int N)
{
	int i;
	int max = 1; // Here be dragons: nu vrem min_int pentru ca merge si cu 1
	for(i = 0; i < N; i++)
		if(max < v[i])
			max = v[i];

	int displayWidth = 2 + log10(max);
	char * aux = malloc(1000*sizeof(char)); 
	char * vectorValue = malloc(10*sizeof(char));
	for(i = 0; i < N; i++) {
		sprintf(vectorValue, "%*i", displayWidth, v[i]);
		strcat(aux, vectorValue);
		strcat(aux, " ");
	}
	printf("%s\n", aux);
}

void print(int * v, int N)
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printAll(v, N);
	else
		printAll(v, N);
}

int vectorContains(int * v, int size, int value) {
	for(int i=0;i<size;i++)
		if(v[i] == value)
			return 1;
	return 0;
}


void cautaDrum(int* data, int n_for_data,int task_id, int thread_id);

Task makeTask(int* path, int n, int task_id) 
{
	Task task;
	int * newData = (int*)malloc(sizeof(int)* n);
	for(int i=0;i<n;i++)
		newData[i]=path[i];
	task.data=newData;
	task.n_for_data=n;
	task.task_id=task_id;
	task.runTask = cautaDrum;
	return task;
}

void cautaDrum(int* data, int n_for_data, int task_id,int thread_id)
{
	if (data[n_for_data-1] == destinationVertex) {
		//print("task-ul %d si am gasit drumul: ",task_id);
		forceShutDownWorkers();
		print(data, n_for_data);
		return;
	}

	// Try to add all possible next nodes that do not create a cycle. 
	int lastNodeInPath = data[n_for_data-1];
	for (int i = 0; i < numEdges; i++) {
		if (graph[i][0] == lastNodeInPath) {
			if (vectorContains(data, n_for_data, graph[i][1]))
				continue;
			int * newPartialPath = malloc(sizeof(int) * 100);
			memcpy ( newPartialPath, data, sizeof(int)*100 );
			newPartialPath[n_for_data] = graph[i][1];
			//getPath(newPartialPath, n_for_data + 1, n_for_data);
			putTask(makeTask(newPartialPath,n_for_data+1,task_id+1));
		}
	}
}

int main(int argc, char** argv) 
{
	getArgs(argc, argv);
	//initDefaultGraph();
	generateGraph(N, 2*N);

	int * partialPath = malloc(sizeof(int) * numVertices);
	partialPath[0] = startVertex;
	//getPath(partialPath, 1, destinationVertex);

	startWorkers();
	putTask(makeTask(partialPath,1,1));
	joinWorkerThreads();
}