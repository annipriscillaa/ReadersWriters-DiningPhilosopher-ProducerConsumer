//gcc rw.c -lpthread -lrt (used for compilation)

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<signal.h>

sem_t mutex,writeblock;
int rcount=0,data=0;

void *writer(void *arg){
	int f;
	f=((int)arg);
	sem_wait(&writeblock);
	data++;
	printf("\nthe data written by the writer %d is %d",f,data);
	sleep(1);
	sem_post(&writeblock);
}

void *reader(void *arg){
	int f;
	f=((int)arg);
	sem_wait(&mutex);
	rcount=rcount+1;
	if(rcount==1){
		sem_wait(&writeblock);
	}
	sem_post(&mutex);
	printf("\nthe data read by the reader %d is %d",f,data);
	sleep(1);
	sem_wait(&mutex);
	rcount=rcount-1;
	if(rcount==0){
		sem_post(&writeblock);
	}
	sem_post(&mutex);
}

int main(){
	int i=0;
	pthread_t wtid[5],rtid[5];
	sem_init(&mutex,0,1);
	sem_init(&writeblock,0,1);
	
	for(i=0;i<=2;i++){
		pthread_create(&wtid[i],NULL,writer,(void *)i);
		pthread_create(&rtid[i],NULL,reader,(void *)i);
	}
	
	for(i=0;i<=2;i++){
		pthread_join(wtid[i],NULL);
		pthread_join(rtid[i],NULL);
	}
	return 0;
}
