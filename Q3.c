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
        
        int arr[100];
        int size;
        
        cout<<"ENTER SIZE"<<endl;
        cin>>size;
        
        for(int i=0;i<size;i++)
        {
            cout<<"ENTER ELEMENT "<<i+1<<endl;
            cin>>arr[i];
        }
        
        write(fd[1],&size,4);
        write(fd[1],arr,sizeof(arr));
        
        close(fd[1]);
    }
    else
    {
        //child
        close(fd[1]);
        
        int arr2[100];
        int size2;
        
        read(fd[0],&size2,4);
        read(fd[0],arr2,size2*4);
        
        cout<<"ARRAY RECEIVED: "<<endl;
        for(int i=0;i<size2;i++)
            cout<<arr2[i]<<endl;
        
        close(fd[0]);
    }
    return 0;
}
