#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int printLevel;
int N;
int *v;
int *vQSort;
int *vNew;
int aux;
int curr_index;
int P;
int sorted = 0;
pthread_barrier_t barrier;

void *threadFunction(void *var)
{
	int thread_id = *(int *)var;
	long i, aux;

	for (int vectsz = 0; vectsz < N; vectsz++) {
		if (vectsz % 2 == 0) {
			int each = N / P;

			if (each % 2 != 0) {
				each += 1;
			}

			int start = thread_id * each;
			int stop = (thread_id + 1) * each;

			if (thread_id == N - 1) {
				stop = N;
			}

			for (i = start; i < stop; i += 2) {
				if (v[i] > v[i + 1]) {
					aux = v[i];
					v[i] = v[i + 1];
					v[i + 1] = aux;
				}
			}
		} else {
			int each = (N - 1) / P;

			if (each % 2 != 0) {
				each += 1;
			}

			int start = thread_id * each + 1;
			int stop = (thread_id + 1) * each + 1;

			if (thread_id == N - 1) {
				stop = N - 1;
			}

			for (i = start; i < stop; i += 2) {
				if (v[i] > v[i + 1]) {
					aux = v[i];
					v[i] = v[i + 1];
					v[i + 1] = aux;
				}
			}
		}
		pthread_barrier_wait(&barrier);
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
	if (argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
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
	int i;
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

int main(int argc, char *argv[])
{
	int i, j, aux;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// sort the vector v
	// PARALLELIZE ME
	pthread_barrier_init(&barrier, NULL, P);

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
	pthread_barrier_destroy(&barrier);

	return 0;
}
