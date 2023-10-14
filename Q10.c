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
int y=10;

void* fun(void* arg)
{
    int * val = (int*)arg;
    cout<<"Value received in thread: "<<*val<<endl;
    
    int* val2 = new int(++y);
    return (void*)val2;
    // return NULL;
}

int main(int argc,char** argv)
{
    void* temp;
    for(int i=0;i<5;i++)
    {
        pthread_create(&threads[i],NULL,&fun,&i);
    }
    
    for(int i=0;i<5;i++)
    {
        pthread_join(threads[i],(void**)&temp);
        cout<<"Value received in main: "<<*(int*)temp<<endl;
    }
    return 0;
}
