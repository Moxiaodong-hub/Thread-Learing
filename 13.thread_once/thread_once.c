#include "include.h"

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_t tid;
void thread_init(){

	printf("once is %d \n", once);
	printf("I am in thread %d \n", tid);
}


void *thread_fun1(void *arg){
	printf("I an thread 1 \n");
	tid = pthread_self();
	printf("once is %d \n", once);
	pthread_once(&once, thread_init);
	printf("once is %d \n",once);
	return NULL;
}
void *thread_fun2(void *arg){
	sleep(2);
	printf("I an thread 2 \n");
	tid = pthread_self();
	pthread_once(&once, thread_init);
	return NULL;
}
int main(){
	pthread_t tid1, tid2;
	int err;
	err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0){
		return 0;
	}
	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		return 0;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}
