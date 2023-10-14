#include<iostream>
#include<unistd.h> // fork() + exec() + dup() + sleep()
#include<sys/wait.h> // wait()
#include<pthread.h> // pthread
#include<string.h> // string
#include<sys/stat.h> //mkfifo()
#include<fcntl.h>  // open()
#include<semaphore.h> // semaphores
using namespace std;

int main(int argc,char** argv)
{
    char* arg[100] = {{"hello"},{"hamza"},NULL};
    
    execv(".\\prog2",arg);
    return 0;
}
