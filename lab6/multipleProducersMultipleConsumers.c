#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

int N;
int P;
int printLevel;
pthread_mutex_t consumeMutex = PTHREAD_MUTEX_INITIALIZER; 

int putIndex = 0;
int getIndex = 0;
sem_t sem_prod;
sem_t sem_cons;
pthread_mutex_t mutex; 

int * rezults;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
	if(P%2 || P<4) {
		printf("P needs to be even and bigger or equal to 4\n");
		exit(1);
	}
}

//THIS IS WHERE YOU HAVE TO IMPLEMENT YOUR SOLUTION
int * buffer;
int BUFFER_SIZE=5;
int get() {

	sem_wait(&sem_cons);
	pthread_mutex_lock(&mutex);

	int aux = buffer[getIndex];
	getIndex++;
	getIndex %= BUFFER_SIZE;

	pthread_mutex_unlock(&mutex);
	sem_post(&sem_prod);
	return aux;

}

void put(int value) {

	sem_wait(&sem_prod);
	pthread_mutex_lock(&mutex);

	buffer[putIndex] = value;
	putIndex++;
	putIndex %= BUFFER_SIZE;

	pthread_mutex_unlock(&mutex);
	sem_post(&sem_cons);

}

//END THIS IS WHERE YOU HAVE TO IMPLEMENT YOUR SOLUTION

void* consumerThread(void *var)
{
	int aux;
    int i;
	for (i = 0; i < N; i++) {
		aux = get();
		pthread_mutex_lock(&consumeMutex);
		rezults[aux]++;
		pthread_mutex_unlock(&consumeMutex);
	}
	return NULL;
}

void* producerThread(void *var)
{
	int i;

	for (i = 0; i < N; i++) {
		put(i);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);

	int i;
	int NPROD=P/2;
	int NCONS=P/2;
	pthread_t tid[NPROD+NCONS];
    buffer = malloc(BUFFER_SIZE * sizeof(int));
	rezults = malloc(N * sizeof(int));
	
    //HERE YOU CAN INIT DECLARE SEMAPHORES
	sem_init(&sem_prod,0,BUFFER_SIZE);
	sem_init(&sem_cons,0,0);
	pthread_mutex_init(&mutex,NULL);


	for(i = 0; i < NPROD; i++) {
		pthread_create(&(tid[i]), NULL, producerThread, NULL);
	}
	for(; i < NPROD+NCONS; i++) {
		pthread_create(&(tid[i]), NULL, consumerThread, NULL);
	}

	for(i = 0; i < NPROD+NCONS; i++) {
		pthread_join(tid[i], NULL);
	}

	for (int i = 0; i < N; i++) {
		if (rezults[i] != NPROD) {
			printf("FAILED, the produced data does not match the consumed data\n");
			exit(1);
		}
	}
	printf("CORRECT\n");

	return 0;
}
