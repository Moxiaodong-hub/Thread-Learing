#include "include.h"

void *thread_fun(void *arc){
	int state;
	printf("I am new thread \n");
	state = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	sleep(2);

	state = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	printf("Cancel success \n");
	
	return (void*)22;
}

int main(){
	pthread_t tid;
	int err, cval, jcal;
	int *rval;

	err = pthread_create( &tid, NULL, thread_fun, NULL);
	if(err != 0){
		printf("create thread faild");
		return 0;
	}
	sleep(1);

	cval = pthread_cancel(tid);
	if(cval != 0){
		printf("cancel thread faild \n");
	}
	rval = pthread_join(tid, &rval);
	return 0;
}
