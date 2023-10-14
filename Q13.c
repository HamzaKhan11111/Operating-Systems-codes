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
sem_t lock;

int x=0;

void* fun(void* arg)
{
    sem_wait(&lock);
    x++;
    cout<<x<<endl;
    sem_post(&lock);
    return NULL;
}

int main(int argc,char** argv)
{
    sem_init(&lock,0,1);
    
    for(int i=0;i<5;i++)
        pthread_create(&threads[i],NULL,&fun,NULL);
        
    for(int i=0;i<5;i++)
        pthread_join(threads[i],NULL);

    pthread_exit(0);
}
