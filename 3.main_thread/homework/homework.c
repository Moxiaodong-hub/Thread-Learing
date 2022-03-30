#include "include.h"

void* print(void *arc){
	for(int i = 0; i < 100; i++){
		printf("new thread is %d\n",2*i);
		sleep(1);
	}
	return (void*)0;
}


int main(){
	
	pthread_t tid;
	int err;
	int *prv;
	err = pthread_create(&tid, NULL, print,"new thread");

	if(err != 0){
		printf("thread create faild");
		return 0;
	}
	for(int i = 0; i < 100; i++){
		printf("main thread is %d\n",2*i+1);
		sleep(1);
	}
	pthread_exit(prv);
	return 0;
}
