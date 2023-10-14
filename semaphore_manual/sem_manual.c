#include<iostream>
#include<unistd.h> // fork() + exec() + dup() + sleep()
#include<sys/wait.h> // wait()
#include<pthread.h> // pthread
#include<string.h> // string
#include<sys/stat.h> //mkfifo()
#include<fcntl.h>  // open()
#include<semaphore.h> // semaphores
using namespace std;

pthread_t threads[5];

int lock=0;
void sem_initialize(int* lock,int x)
{
	*lock=x;
}

void sem_waiting(int *l)
{
	while(*l<=0);
	*l--;
}

void sem_posting(int *l)
{
	*l++;
}


int x=0;

void* fun(void* arg)
{
    sem_waiting(&lock);
    x++;
    cout<<x<<endl;
    sem_posting(&lock);
    return NULL;
}

int main(int argc,char** argv)
{
    sem_initialize(&lock,1);
    
    for(int i=0;i<5;i++)
        pthread_create(&threads[i],NULL,&fun,NULL);
        
    for(int i=0;i<5;i++)
        pthread_join(threads[i],NULL);

    pthread_exit(0);
}
