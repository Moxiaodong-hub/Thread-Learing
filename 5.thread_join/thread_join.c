#include "include.h"

void *thread_fun1(void *arc){
	printf("I am thread1 \n");
	return (void *)1;
}


void *thread_fun2(void *arc){
	printf("I am thread2 \n");
	pthread_detach(pthread_self());
	pthread_exit((void *)2);
}

int main(){
	int err1, err2;
	pthread_t tid1, tid2;
	void* tval1, *tval2;

	err1 = pthread_create(&tid1, NULL, thread_fun1, NULL);
	err2 = pthread_create(&tid2, NULL, thread_fun2, NULL);

	if(err1 || err2){
		printf("create thread faild\n");
		return 0;

	}
	printf("I am main thread\n");
	printf("join1 rval is %d\n", pthread_join(tid1, &tval1));
	printf("join2 rval is %d\n", pthread_join(tid2, &tval2));

	printf("thread 1 exit code is %d\n", (int *)tval1);
	printf("thread 2 exit code is %d\n", (int *)tval2);
	return 0;
}
