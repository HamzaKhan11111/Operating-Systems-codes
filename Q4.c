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
        //parent
        close(fd[0]);
        
        char arr[100];
        int size;
        
        cout<<"ENTER SIZE"<<endl;
        cin>>size;
        
        cout<<"ENTER ARRAY"<<endl;
        cin>>arr;
        
        write(fd[1],&size,4);
        write(fd[1],arr,size);
        
        close(fd[1]);
    }
    else
    {
        //child
        close(fd[1]);
        
        char arr2[100];
        int size2;
        
        read(fd[0],&size2,4);
        read(fd[0],arr2,size2);
        
        cout<<"ARRAY RECEIVED: "<<endl;
        cout<<arr2<<endl;
        
        close(fd[0]);
    }
    return 0;
}
