#include "include.h"

struct student{
	char name[20];
	int age;
};
void print(void *arc)
{
	printf("name = %s,age = %d\n",((struct student *)arc)->name, ((struct student *)arc)->age);
}

void *func(void *arc)
{
	print(arc);
	return (void *)0;
}

int main()
{
	struct student dong;
	int err;
	memcpy(dong.name, "dong", 20);
	dong.age = 20;
	pthread_t tid;
	err = pthread_create(&tid, NULL, func, (void*)&dong);
	
	if(err != 0)
	{
		printf("create thread faild\n");
		return 0;
	}	
	printf("create thread success\n");
	sleep(1);
	return 0;
}
