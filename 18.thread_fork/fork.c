#include "include.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void prepare(){
	printf("I am prepare\n");
	pthread_mutex_lock(&mutex);
}
void child(){
	printf("I am child\n");
	pthread_mutex_unlock(&mutex);
}
void parent(){
	printf("I am parent\n");
	pthread_mutex_unlock(&mutex);
}

void *thread_fun(void *arg){
	sleep(1);
	pid_t pid;
	pthread_atfork(prepare, parent, child);

	pid = fork();
	if(pid == 0){
		pthread_mutex_lock(&mutex);
		printf("child process \n");
		pthread_mutex_unlock(&mutex);
	}
	else{
		pthread_mutex_lock(&mutex);
		printf("parent process \n");
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_t tid;

	if(pthread_create(&tid, NULL, thread_fun, NULL)){
		printf("create thread faild \n");
		return 0;
	}
	pthread_mutex_lock(&mutex);
	sleep(2);
	pthread_mutex_unlock(&mutex);
	pthread_join(tid, NULL);
	return 0;

}
