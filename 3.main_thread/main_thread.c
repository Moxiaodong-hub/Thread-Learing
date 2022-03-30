#include "include.h"

struct student{
	char name[20];
	int age;
};

void *thread_fun(void *arc){
	printf("student age is %d, name is %s\n",((struct student *)arc)->age, ((struct student *)arc)->name);
	return (void *)0;
}

int main(int argc, char * argv[]){
	pthread_t tid;
	int err;
	
	struct student stu;
	stu.age = 20;
	memcpy(stu.name, "zhangsan", 20);

	err = pthread_create(&tid, NULL, thread_fun, (void *)&stu);

	if(err !=0 ){
		printf("create thread faild\n");
		return 0;
	}

	for(int i = 0; i < argc; i++){
		printf("main thread args is %s\n", argv[i]);
	}
	sleep(2);
	return 0;
}
