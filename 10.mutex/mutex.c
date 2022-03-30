#include "include.h"

//定义结构体
struct student{
	int id;
	int num;
	int key;
}stu;
int i = 0;

//定义全局互斥量
pthread_mutex_t mutex;

//定义子线程函数
void *thread_fun1(void *arc){
	while(1){
		pthread_mutex_lock(&mutex);
		stu.id = i;
		stu.num = i;
		stu.key = i;
		i++;
		if(stu.id != stu.num || stu.id!=stu.key || stu.num!=stu.key){
			printf("%d  %d  %d \n", stu.num, stu.id, stu.key);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	return (void *)0;
}
void *thread_fun2(void *arc){
	while(1){
		pthread_mutex_lock(&mutex);
		stu.id = i;
		stu.num = i;
		stu.key = i;
		i++;
		if(stu.id != stu.num || stu.id!=stu.key || stu.num!=stu.key){
			printf("%d  %d  %d \n", stu.num, stu.id, stu.key);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	return (void *)0;
}


int main(){
	pthread_t tid1, tid2;
	int err;
	pthread_mutex_init(&mutex, NULL);//初始化互斥量

	err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0){
		printf("create thread 1 faild \n");
		return 0;
	}
	err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0){
		printf("create thread 2 faild \n");
		return 0;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}
