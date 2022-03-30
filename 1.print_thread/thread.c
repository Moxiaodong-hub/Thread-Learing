#include "include.h"

int main(){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("pid = %u /n, tid = %u \n",pid, tid);
	return 0;
}

