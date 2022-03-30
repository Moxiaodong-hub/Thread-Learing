#include "include.h"

pthread_rwlock_t rwlock;
int num = 0;

void *thread_fun1(void *arc){
	printf("thread 1 excuse \n");
	pthread_rwlock_rdlock(&rwlock);
	sleep(2);
	printf("thread 1 num = %d\n", num);
	pthread_rwlock_unlock(&rwlock);
	return (void *)0;
}
void *thread_fun2(void *arc){
	printf("thread 2 excuse \n");
	pthread_rwlock_rdlock(&rwlock);
	sleep(2);
	printf("thread 2 num = %d\n", num);
	pthread_rwlock_unlock(&rwlock);
	return (void *)0;
}
int main(){
	pthread_t tid1, tid2;
	int err;
	pthread_rwlock_init(&rwlock, NULL);

	err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0){
		printf("create thread faild \n");
		return 0;
	}
	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		printf("create thread faild \n");
		return 0;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_rwlock_destroy(&rwlock);
	return 0;
	
}
