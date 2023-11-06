#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include<iostream>
using namespace std;

int main()
{
    int fd1[2];
    int fd2[2];
    
    if(pipe(fd1)<0||pipe(fd2)<0)
    {
        return 0;
    }
    
    if(fork())
    {
        close(fd1[0]);
        close(fd2[1]);
        while(1)
        {
            char arr1[100];
            printf("%s","Parent sent: ");
            cin.getline(arr1,100);
            write(fd1[1],arr1,100);
            if(arr1[0]=='q'||arr1[0]=='Q')
            {
                printf("%s","Parent: Q or q entered. Process exiting\n");
                break;
            }
            
            read(fd2[0],arr1,100);
            
            printf("%s","Received from Child: ");
           
             cout<<endl;
             write(1,arr1,strlen(arr1));
             cout<<endl;
        }
         sleep(2);
        wait(NULL);
       
    }
    
    else
    {
        //close(fd2[0]);
        //close(fd1[1]);
        
        while(1)
        {
            
            char arr2[100];
            read(fd1[0],arr2,100);
            
            printf("%s","Received from Parent: ");
            cout<<endl;
            write(1,arr2,strlen(arr2));
            cout<<endl;
            //printf("%s\n",arr2);
            if(arr2[0]=='q'||arr2[0]=='Q')
            {
            	
                printf("%s","Child: Q or q entered. Process exiting\n");
                break;
            }
            
           
            printf("%s","Child sent: ");
            cout<<endl;
            cin.getline(arr2,100);
            write(fd2[1],arr2,100);
            
        }
       // sleep(2);
    }
    


    return 0;
}