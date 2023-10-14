#include<iostream>
#include<unistd.h> // fork() + exec() + dup() + sleep()
#include<sys/wait.h> // wait()
#include<pthread.h> // pthread
#include<string.h> // string
#include<sys/stat.h> //mkfifo()
#include<fcntl.h>  // open()
#include<semaphore.h> // semaphores
using namespace std;

int main()
{
    mkfifo("mypipe",0777);
    int fd = open("mypipe.txt",O_RDWR | O_CREAT , 0777);
    
    dup2(1,fd);
    
    char arr[100];
    cin>>arr;
    write(fd,arr,strlen(arr));
    
    return 0;
}
