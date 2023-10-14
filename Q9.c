#include<iostream>
#include<unistd.h> // fork() + exec() + dup() + sleep()
#include<sys/wait.h> // wait()
#include<pthread.h> // pthread
#include<string.h> // string
#include<sys/stat.h> //mkfifo()
#include<fcntl.h>  // open()
#include<semaphore.h> // semaphores
using namespace std;

//terminal > .\main .\reader .\writer

// main.cpp
int main(int argc,char** argv)
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
            execlp(argv[1],to_string(fd[0]));
        }
    }
    else
    {
        execlp(argv[2],to_string(fd[1]));
    }
    return 0;
}

//writer.cpp
int main(int argc,char** argv)
{
    int val = int(argv[1]);
    char a[10];
    fgets(a,10,stdin);
    write(val,a,10);
    return 0;
}

//reader.cpp
int main(int argc,char** argv)
{
    int val = int(argv[1]);
    char a[10];
    read(val,a,10);
    return 0;
}
