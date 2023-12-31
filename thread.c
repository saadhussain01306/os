#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *sum(void *arg);
void *mul(void *arg);
long int sm = 0, prod = 1;
void main(int argc, char *argv[])
{
    pthread_t T1, T2;
    pthread_attr_t attr;      
    pthread_attr_init(&attr); 
    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);
    printf("Inside main thread\n");
    printf("sum=%ld\n", sm);
    printf("product=%ld\n", prod);
}
void *sum(void *parm)
{
    int i, n;
    n = atoi(parm); 
    printf("inside  sum thread\n");

    for (i = 1; i <= n; i++)
    {
        sm += i;
    }
    printf("sum thread completed\n");
}
void *mul(void *parm)
{
    int i, n;
    n = atoi(parm);
    printf("inside mul thread\n");
    for (i = 2; i <= n; i++)
    {
        prod = prod * i;
    }
    printf("mul thread completed  product\n");
}

/*
gcc -o thread thread.c -pthread
./thread 5
inside  sum thread
sum thread completed
inside mul thread
mul thread completed  product
Inside main thread
sum=15
product=120
*/
