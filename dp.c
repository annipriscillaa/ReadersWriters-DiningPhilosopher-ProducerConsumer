#include<stdio.h>
#include<time.h>

int ph[4],semaphore[5];//no.of chopsticks

void state(){
	int i=0;
	for(i=0;i<4;i++){
		switch(ph[i]){
			case 0:printf("\nphilosopher %d is thinking",i);break;
			case 1:printf("\nphilosopher %d is hungry",i);break;
			case 2:printf("\nphilosopher %d is eating",i);break;
		}
	}
}

void wait(int *S){
	while((*S)<=0);
	(*S)--;
}

void signal(int *S){
	(*S)++;
}

void philosopher(int p){
	ph[p]=1;
	state();
	printf("\n\n");
	wait(&semaphore[p]);
	wait(&semaphore[(p+1)%5]);
	ph[p]=2;
	state();
	printf("\n\n");
	signal(&semaphore[p]);
	signal(&semaphore[(p+1)%5]);
	ph[p]=0;
	state();
	printf("\n\n");
}

int main(){
	int i=0,ch=0;
	for(i=0;i<4;i++){
		ph[i]=0;
	}
	
	for(i=0;i<5;i++){
		semaphore[i]=1;
	}
	
	state();
	printf("\n\n");
	srand(time(0));
	
	i=0;
	
	while(i<=3){
		int x=rand();
		ch=x%5;//no.of chopsticks
		switch(ch){
			case 0:philosopher(0);printf("\n\n");break;
			case 1:philosopher(1);printf("\n\n");break;
			case 2:philosopher(2);printf("\n\n");break;
			case 3:philosopher(3);printf("\n\n");break;
		}
		i++;
	}
}
