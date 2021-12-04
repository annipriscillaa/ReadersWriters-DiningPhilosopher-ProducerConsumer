#include<stdio.h>
#include<time.h>

int sema[3],cnt=0,in=0,out=0,buf[10],max_size=2;

void wait(int *S){
	while((*S)<=0);
	((*S)--);
}

void signal(int *S){
	(*S)++;
}

void producer(int p){
	wait(&sema[1]);
	wait(&sema[2]);
	buf[in]=p;
	printf("\nproduced item number:%d",in+1);
	cnt++;
	in=(in+1)%max_size;
	signal(&sema[2]);
	signal(&sema[0]);
}

void consumer(){
	wait(&sema[0]);
	wait(&sema[2]);
	int q=buf[out];
	printf("\nconsumed item number:%d",q);
	cnt--;
	out=(out+1)%max_size;
	signal(&sema[2]);
	signal(&sema[1]);
}

int main(){
	sema[0]=0;//full
	sema[1]=max_size;//empty
	sema[2]=1;//mutex
	int i=0;
	srand(time(0));
	
	while(i<10){
		int x=rand();
		printf("\nthe random number generated is %d",x);
		if(x%2==0){
			if(sema[0]==max_size){
				printf("\nthe buffer is full");
			}else{
				producer(in+1);
			}
		}else{
			if(sema[1]==max_size){
				printf("\nthe buffer is empty");
			}else{
				consumer();
			}
		}
		printf("\n\n");
		i++;
	}
	return 0;
}
