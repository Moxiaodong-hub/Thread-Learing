#include "include.h"

void *first_clean(void *arc){
	printf("%s first clean\n", (char*)arc);
	return (void *)0;
}
void *second_clean(void *arc){
	printf("%s second clean\n", (char *)arc);
	return (void *)0;
}
void *thread_fun1(void *arc){
	printf("new thread 1 \n");
	pthread_cleanup_push(first_clean, "thread1");
	pthread_cleanup_push(second_clean, "thread1");

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);

	return (void *)0;
}
void *thread_fun2(void *arc){
	printf("new thread 2 \n");
	pthread_cleanup_push(first_clean, (void *)"thread2");
	pthread_cleanup_push(second_clean, (void *)"thread2");

	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);

	return (void *)0;
}
int main(){
	pthread_t tid1, tid2;
	int err;

	err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0){
		printf("create new thread faild\n");
		return 0;
	}
	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		printf("create new thread faild\n");
		return 0;
	}
	sleep(2);
	return 0;
}
