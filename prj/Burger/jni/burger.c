#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<semaphore.h>

sem_t receive_sem,rack_sem,burger_sem,cash_free_sem,mutex;
int cook_num,cashier_num,customer_num,rack_size,cusServe=0,serve_num=0,bur_num_total=0;

void* Cook(void *t)
{
	int cook_index = *(int*)t;
	//sleep(1);
	srand(cook_index);
	int time = rand()%2;
	while(1)
	{
		sem_wait(&mutex);
		if(bur_num_total >= customer_num)
		{
			sem_post(&mutex);
			break;
		}
		else
		{
			bur_num_total++;
			sem_post(&mutex);
		}
		
		sleep(time);
		sem_wait(&rack_sem);
		sem_post(&burger_sem);
		
		printf("Cooks[%d] makes a burger.\n",cook_index);
	}
	return NULL;
}

void* Cashier(void *t)
{
	int cashier_index = *(int*)t;
	//srand(cashier_index);
//	int time = rand()%3;
	while(1)
	{
		sem_wait(&mutex);
		if(serve_num >= customer_num)
		{
			sem_post(&mutex);
			break;
		}
		else
		{
			serve_num++;
			sem_post(&mutex);
		//	icusServe++;
		}
		
		sem_wait(&receive_sem);
		
		printf("Cashier[%d] accepts an order.\n",cashier_index);
		sem_wait(&burger_sem);
		printf("Cashier[%d] takes a burger to customer.\n",cashier_index);
		sem_post(&rack_sem);
		sem_post(&cash_free_sem);
	}
	return NULL;
}

void* Customer(void*t)
{
	int customer_index = *(int*)t;
	srand(customer_index);
	int time = rand()%2;
	sleep(time);

	printf("Customer[%d] comes\n",customer_index);

	sem_wait(&cash_free_sem);
	sleep(time);
	sem_post(&receive_sem);
	return NULL;
}

void *detect(void*t)
{
	wait(&mutex);
	int i = 0;
	for(i=0;i<cook_num;i++)
	{
		sem_post(&rack_sem);
	}
	for(i=0;i<cashier_num;i++)
	{
		sem_post(&receive_sem);
	}
	
}


int main(int argc,void*argv[])
{	
	pthread_t* thread_id;

	printf("Please input the number of cook,cashier,customer and rack size.\n");
	scanf("%d%d%d%d",&cook_num,&cashier_num,&customer_num,&rack_size);
	printf("Cooks[%d],Cashiers[%d],Customers[%d]\n",cook_num,cashier_num,customer_num);
	printf("Begin run\n");
	thread_id = (pthread_t*)malloc(sizeof(pthread_t)*(cook_num+cashier_num+customer_num+rack_size+5));
	sem_init(&cash_free_sem,cashier_num,cashier_num);
	sem_init(&receive_sem,cashier_num,0);
	sem_init(&burger_sem,rack_size,0);
	sem_init(&mutex,1,1);
	sem_init(&rack_sem,rack_size,rack_size);
	int index=0;
	int*cook_id,*cashier_id,*customer_id;
	cook_id = (int*)malloc(cook_num*sizeof(int));
	cashier_id = (int*)malloc(cashier_num*sizeof(int));
	customer_id = (int*)malloc(customer_num*sizeof(int));
	int i;
	for(i=1;i<=cook_num;i++)
	{
		cook_id[i-1] = i;
		pthread_create(&thread_id[index++],NULL,Cook,&cook_id[i-1]);
	}
	for(i=1;i<=cashier_num;i++)
	{
		cashier_id[i-1] = i;
		pthread_create(&thread_id[index++],NULL,Cashier,&cashier_id[i-1]);
	}
	for(i=1;i<=customer_num;i++)
	{
		customer_id[i-1] = i;
		pthread_create(&thread_id[index++],NULL,Customer,&customer_id[i-1]);
	}
	int  tmp;
//	pthread_create(&thread_id[index++],NULL,detect,&tmp);
	for(i=0;i<index;i++)
	{
		pthread_join(thread_id[i],NULL);
	}
	printf("\nFinish!\n");
	
	return 0;
}
