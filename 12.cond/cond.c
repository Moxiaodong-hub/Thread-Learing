#include "include.h"

#define BUFF_SIZE 5
#define PRODUCT_CNT 30

struct product{
	int buffer[BUFF_SIZE];
	pthread_mutex_t lock;
	int readpos, writepos;
	pthread_cond_t notempty;
	pthread_cond_t notfull;
}buffer;

void init(struct product *p){
	pthread_mutex_init(&p->lock, NULL);
	pthread_cond_init(&p->notempty, NULL);
	pthread_cond_init(&p->notfull, NULL);
	p->readpos = 0;
	p->writepos = 0;
}

void finish(struct product *p){
	pthread_mutex_destroy(&p->lock);
	pthread_cond_destroy(&p->notempty);
	pthread_cond_destroy(&p->notfull);
}

void put(struct product *p, int data){
	pthread_mutex_lock(&p->lock);
	if((p->writepos+1)%BUFF_SIZE == p->readpos){
		printf("buffer is full waiting get out \n");
		pthread_cond_wait(&p->notfull, &p->lock);
	}
	p->buffer[p->writepos] = data;
	p->writepos ++;
	if(p->writepos >= BUFF_SIZE)
		p->writepos = 0;
	pthread_cond_signal(&p->notempty);
	pthread_mutex_unlock(&p->lock);
}
int get(struct product *p){
	int data;
	pthread_mutex_lock(&p->lock);
	if(p->writepos == p->readpos){
		printf("buffer is empty waiting put in \n");
		pthread_cond_wait(&p->notempty, &p->lock);
	}
	data = p->buffer[p->readpos];
	p->readpos ++;
	if(p->readpos >= BUFF_SIZE)
		p->readpos = 0;
	pthread_cond_signal(&p->notfull);
	pthread_mutex_unlock(&p->lock);
	return data;
}

void *produtor(void *data){
	for(int i = 0; i <= 50; i++){
		sleep(1);
		printf("puting the product ...\n");
		put(&buffer, i);
		printf("put the %d product success \n",i);
	}
	printf("productor stopped \n");
	return (void *)0;
}

void *consumer(void *data){
	static int cnt = 0;
	int num;
	while(1){
		sleep(2);
		printf("geting product ....\n");
		num = get(&buffer);
		printf("get the %d product success \n",num);
		if(++cnt == PRODUCT_CNT)
			break;
	}
	printf("consumer stopped \n");
	return (void *)0;
}

int main(){
	pthread_t tid1, tid2;
	int err;
	init(&buffer);
	err = pthread_create(&tid1, NULL, produtor,NULL);
	if(err != 0){
        	printf("create thread faild \n");
		return 0;
	}
	err = pthread_create(&tid2, NULL, consumer,NULL);
	if(err != 0){
		printf("create thread faild \n");
		return 0;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	finish(&buffer);
	return 0;	
	       


}
