#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd1=open("file.txt",O_RDWR|O_CREAT,0777);
    int fd2=dup(fd1);
    
    int fd1_cpy = dup(fd1);
    int fd2_cpy = dup(fd2);
    
    int r1=10;
    int r2=10;
    
    char arr[100];
    int i=0;
    while(1)
    {

        if( i%2 == 0)
        {
            r1 =read(fd1,arr,1);
            if(r1==0)
                break;
            dup2(1,fd1);
            write(fd1,arr,strlen(arr));
            
        }
        else
        {
            r2 = read(fd2,arr,1);
            if(r2==0)
                break;
            dup2(1,fd2);
            write(fd2,arr,strlen(arr));
            
        }
        i++;
        dup2(fd1_cpy,fd1);
        dup2(fd2_cpy,fd2);
    }
    
    dup2(fd1_cpy,fd1);
    dup2(fd2_cpy,fd2);
    
    close(fd1);
    close(fd2);
    
    return 0;
}

