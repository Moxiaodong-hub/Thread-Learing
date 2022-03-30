#include "include.h"

void *thread_fun1(void *arc){
	printf("I am thread 1 \n");
	return (void *)0;
}
void *thread_fun2(void *arc){
	printf("I am thread 2 \n");
	return (void *)0;
}

int main(){
	pthread_t tid1, tid2;
	int err;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	err = pthread_create(&tid1, &attr, thread_fun1, NULL);
	if(err != 0){
		printf("thread 1 creat faild \n");
		return 0;
	}
	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		printf("thread 2 creat faild \n");
		return 0;
	}
	
	pthread_join(tid1, NULL);
	if(!err)
		printf("join pthread 1 success \n");
	else
		printf("join pthread 1 faild \n");
		
	err = pthread_join(tid2, NULL);
	if(err)
		printf("join pthread 2 success \n");
	else
		printf("join pthread 2 faild \n");
	pthread_attr_destroy(&attr);
	
	return 0;
}			

