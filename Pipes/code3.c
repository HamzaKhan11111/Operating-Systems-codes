#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd1=open("file.txt",O_WRONLY|O_CREAT,0777);
    int fd2=dup(fd1);
    
    int stdo = dup(1);
    int i=2;
    char arr[100];
    char arr2[]="hamza";
    while(strncmp(arr,arr2,5))
    {
        fgets(arr,100,stdin);
        if( i%2 == 0)
        {
            dup2(fd1,1);
            printf("%s",arr);
            fflush(stdout);
        }
        else
        {
            dup2(fd2,1);
            printf("%s",arr);
            fflush(stdout);
        }
        i++;
    }
    
    dup2(stdo,1);
    
    close(fd1);
    close(fd2);
    
    return 0;
}

