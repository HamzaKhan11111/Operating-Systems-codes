#include<iostream>
#include<unistd.h> // fork() + exec() + dup() + sleep()
#include<sys/wait.h> // wait()
#include<pthread.h> // pthread
#include<string.h> // string
#include<sys/stat.h> //mkfifo()
#include<fcntl.h>  // open()
#include<semaphore.h> // semaphores
using namespace std;

pthread_t thread;
pthread_attr_t attribute;

void* fun(void* arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    return NULL;
}

int main(int argv,char** argc)
{
    pthread_attr_init(&attribute);
    pthread_attr_setdetachstate(&attribute,PTHREAD_CREATE_DETACHED);
    pthread_create(&thread,&attribute,&fun,NULL);
    
    return 0;
}
