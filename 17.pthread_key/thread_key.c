#include "include.h"

pthread_key_t key; //定义全局私有变量

void *thread_fun1(void *arc){
	printf("I am thread 1\n");
	int a = 1;
	pthread_setspecific(key, (void *)a);
	sleep(2);
	printf("thread 1 key->val is %d \n", pthread_getspecific(key));
	return NULL;
}
void *thread_fun2(void *arc){
	printf("I am thread 2\n");
	sleep(1);
	int a = 2;
	pthread_setspecific(key, (void *)a);
	printf("thread r21 key->val is %d \n", pthread_getspecific(key));
	return NULL;
}

int main(){
	pthread_t tid1, tid2;
	pthread_key_create(&key,NULL);

	if(pthread_create(&tid1, NULL, thread_fun1, NULL)){
		printf("create thread 1 faild");
		return 0;
	}
	if(pthread_create(&tid2, NULL, thread_fun2, NULL)){
		printf("create thread 2 faild");
		return 0;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_key_delete(key);

	return 0;
}
