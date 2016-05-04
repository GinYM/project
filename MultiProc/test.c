#include<pthread.h>
#include<stdio.h>

void *PrintHello(void*threadID){
	long tid;
	tid = (long)threadID;
	printf("Hello World! It's a thread #%ld!\n",tid);
	pthread_exit(NULL);
}

int main(int argc,char*argv[])
{
	pthread_t threads[5];
	int rc;
	long t;
	for(t=0;t<5;t++)
	{
		printf("In main: creating thread %ld\n",t);
		rc=pthread_create(&threads[t],NULL,PrintHello,(void*)t);
		if(rc){
			printf("Error; RETURN code from pthread_create() is %d\n",rc);
			exit(-1);
		}
	}

	pthread_exit(NULL);
}

