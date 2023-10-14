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
    int fd[2];
    pipe(fd);
    
    if(fork())
    {
        if(fork())
        {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
        else
        {
            //c1
            close(fd[0]);
            dup2(fd[1],1);
            execlp("ping","ping","-c","5","google.com",NULL);
        }
    }
    else
    {
        //c2
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("grep","grep","rtt",NULL);
    }
    return 0;
}
