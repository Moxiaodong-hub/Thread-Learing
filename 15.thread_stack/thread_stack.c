#include "include.h"
#include "limits.h"

pthread_attr_t attr;

void *thread_fun(void *arc){
	size_t stacksize;
	printf("I am thread \n");
#ifdef _POSIX_THREAD_ATTR_STACKSIZE  //宏定义判断是否可以修改栈大小
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("stack size is %d\n", stacksize);  //设置栈为最小
#endif
	return NULL;
}

int main(){
	pthread_t tid;
	int err;

	pthread_attr_init(&attr);//初始化属性变量
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);//设置属性变量为可加入
#ifdef _POSIX_THREAD_ATTR_STACKSIZE  //宏定义判断是否可以修改栈大小
	pthread_attr_setstacksize(&attr, 131073);  //设置栈为最小
#endif

	err = pthread_create(&tid, &attr, thread_fun, NULL);
	if(err != 0){
		printf("create thread faild \n");
		return 0;
	}
	pthread_join(tid, NULL);
	pthread_attr_destroy(&attr);

	return 0;
}
