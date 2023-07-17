#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxItems 3 
#define BufferSize 3 

sem_t empty;
sem_t full; 
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
	
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); 
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *pno)
{   
		
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
	int item=buffer[out];
        printf("Consumer %d: Remove Item %d at %d\n", *((int *)pno),item,out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){
pthread_t pro[3],con[3];


pthread_mutex_init(&mutex,NULL);
sem_init(&empty,0,BufferSize);
sem_init(&full,0,0);

int arr[3]={1,2,3};

for(int i=0; i<3; i++){
pthread_create(&pro[i],NULL, (void *)producer, (void *)&arr[i]);
}
for(int i=0; i<3; i++){
pthread_create(&con[i],NULL, (void *)consumer, (void *)&arr[i]);
}
    for(int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}
/*
gcc -o pro_con pro_con.c -pthread
Producer 1: Insert Item 1804289383 at 0
Consumer 1: Remove Item 1804289383 at 0
Producer 1: Insert Item 1714636915 at 1
Producer 3: Insert Item 846930886 at 2
Consumer 2: Remove Item 1714636915 at 1
Producer 1: Insert Item 1957747793 at 0
Consumer 1: Remove Item 846930886 at 2
Consumer 1: Remove Item 1957747793 at 0
Producer 2: Insert Item 1681692777 at 1
Producer 2: Insert Item 719885386 at 2
Producer 2: Insert Item 1649760492 at 0
Consumer 3: Remove Item 1681692777 at 1
Consumer 3: Remove Item 719885386 at 2
Consumer 3: Remove Item 1649760492 at 0
Producer 3: Insert Item 424238335 at 1
Producer 3: Insert Item 596516649 at 2
Consumer 2: Remove Item 424238335 at 1
Consumer 2: Remove Item 596516649 at 2
*/
