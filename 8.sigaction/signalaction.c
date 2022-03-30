#include "include.h"

void sig_handler1(void){
	printf("thread 1 get signal \n");
	return ;
}
void sig_handler2(void){
	printf("thread 2 get signal \n");
	return ;
}
void *thread_fun1(void *arc){
	printf("new thread 1\n");

	struct sigaction act1;
	memset(&act1, 0, sizeof(act1));
	sigaddset(&act1.sa_mask, SIGQUIT);
	act1.sa_handler = sig_handler1;
	sigaction(SIGQUIT, &act1, NULL);

	pthread_sigmask(SIG_BLOCK, &act1.sa_mask, NULL);
	sleep(2);
}

void *thread_fun2(void *arc){
	printf("new thread 2\n");

	struct sigaction act;
	memset(&act, 0, sizeof(act));
//	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_handler = sig_handler2;
	sigaction(SIGQUIT, &act, NULL);

	//pthread_sigmask(SIG_BLOCK, &act.mask, NULL)
	sleep(2);
}

int main(){
	pthread_t tid1, tid2;
	int err;
	int s;
	err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0){
		printf("create thread 1 faild\n");
		return 0;
	}

	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		printf("create thread 2 faild\n");
		return 0;
	}
	
	sleep(1);

	s = pthread_kill(tid1, SIGQUIT);
	if(s != 0){
		printf("send signal thread 1 faild\n");
	}

	s = pthread_kill(tid2, SIGQUIT);
	if(s != 0){
		printf("send signal thread 2 faild\n");
	}
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
