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
    int fd = open("mypipe",O_RDWR);
    
    int x=10;
    int y;
    
    write(fd,&x,4);
    
    read(fd,&y,4);
    
    cout<<y;
    return 0;
}
