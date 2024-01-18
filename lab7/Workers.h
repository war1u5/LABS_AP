#include <pthread.h>
#define QUEUE_SIZE 1000000
extern int P;
 
extern int gotTasks;
extern int putTasks;

typedef struct Task {
	pthread_mutex_t waitUntilFinished;
	void (*runTask)(int*, int, int, int );
	int* data;
	int n_for_data;
	int task_id;
}Task;

void forceShutDownWorkers();
void putTask(Task task);
void startWorkers();
void joinWorkerThreads();