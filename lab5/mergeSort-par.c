#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int NReps;
int printLevel;
int N;
int *v;
int *vQSort;
int *vNew;
int P;

pthread_barrier_t bar;
pthread_mutex_t mux;

void merge(int source[], int start, int mid, int end, int destination[])
{
	// DO NOT MODIFY
	int iA = start;
	int iB = mid;
	int i;

	for (i = start; i < end; i++) {
		if (end == iB || (iA < mid && source[iA] <= source[iB])) {
			destination[i] = source[iA];
			iA++;
		} else {
			destination[i] = source[iB];
			iB++;
		}
	}
}

void compareVectors(int *a, int *b)
{
	// DO NOT MODIFY
	int i;
	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int *v)
{
	// DO NOT MODIFY
	int i;
	int max = 1;
	for (i = 0; i < N; i++)
		if (max < log10(v[i]))
			max = log10(v[i]);
	int displayWidth = 2 + max;
	for (i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
		if (!((i + 1) % 20))
			printf("\n");
	}
	printf("\n");
}

int cmp(const void *a, const void *b)
{
	// DO NOT MODIFY
	int A = *(int *)a;
	int B = *(int *)b;
	return A - B;
}

void getArgs(int argc, char **argv)
{
	if (argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);

	if (log2(N) != (int)log2(N)) {
		printf("N needs to be a power of 2\n");
		exit(1);
	}

	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	vNew = malloc(sizeof(int) * N);
	if (v == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	// generate the vector v with random values
	// DO NOT MODIFY
	srand(42);
	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}

void printPartial()
{
	compareVectors(v, vQSort);
}

void printAll()
{
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v, vQSort);
}

void print()
{
	if (printLevel == 0)
		return;
	else if (printLevel == 1)
		printPartial();
	else
		printAll();
}

void *threadFunction(void *var)
{
	int thread_id = *(long *)var;
	int i;

	int width, *aux;

	int start = thread_id * ceil(N / P);
	int stop = fmin(N, (thread_id + 1) * ceil(N / P));

	for (width = 1; width < N; width = 2 * width) {
		start = (start / (2 * width)) * 2 * width;
		stop = (stop / (2 * width)) * 2 * width;

		for (i = start; i < stop; i = i + 2 * width) {
			merge(v, i, i + width, i + 2 * width, vNew);
		}

		pthread_barrier_wait(&bar);
		pthread_mutex_lock(&mux);

		if (thread_id == 0) {
			aux = v;
			v = vNew;
			vNew = aux;
		}
		pthread_mutex_unlock(&mux);

		pthread_barrier_wait(&bar);
	}
}

int main(int argc, char **argv)
{
	int i;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	pthread_barrier_init(&bar, NULL, P);
	pthread_mutex_init(&mux, NULL);

	pthread_t tid[P];
	int thread_id[P];
	for (i = 0; i < P; i++)
		thread_id[i] = i;

	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	return 0;
}
