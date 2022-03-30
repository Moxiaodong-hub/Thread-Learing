#include "include.h"

void* thread_fun(void *arc){
	if(strcmp("1", (char *)arc) == 0){
		printf("nwe thread return \n");
		return (void *)1;
	}
	if(strcmp("2", (char *)arc) == 0){
		printf("new thread pthread_exit\n");
		pthread_exit((void *)2);
 	}
	if(strcmp("3", (char *)arc) == 0){
		printf("new thread exit\n");
		exit(3);
 	}		
}

int main(int argc, char* argv[]){
	int err;
	pthread_t tid;

	err = pthread_create(&tid, NULL, thread_fun, (void *)argv[1]);
	if(err != 0){
		printf("creat new thread faild\n");
		return 0;
	}
	printf("main thread");
	sleep(1);
}
