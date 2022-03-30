#include "include.h"

void *thread_fun(void *arc){
	sleep(1);
	printf("I am new thread\n");
	return (void *)0;
}

int main(){
	pthread_t tid;
	int err;
	int s;
	int *rval;

	err = pthread_create(&tid, NULL, thread_fun, NULL);
	if(err != 0){
		printf("thread create faild\n");
		return 0;
	}

	sleep(1);

	s = pthread_kill(tid, 0);
	if(s == ESRCH){
		printf("thread is not found \n");
	}
	pthread_join(tid, &rval);
	return 0;
}
