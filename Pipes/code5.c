#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int main()
{
    int fd1[2];
    int fd2[2];
    int fd3[2];
    if(pipe(fd1)==-1 || pipe(fd2)==-1 || pipe(fd3)==-1 )
    {
        printf("ERROR");
    }

    if(fork())
    {
        //closing pipes
        close(fd1[0]); // dont need to read from C1
        close(fd2[0]); // f2 only used between C1,C2
        close(fd2[1]); // f2 only used between C1,C2
        close(fd3[1]); // dont need to write to C2
        
    
        // parent will send this array
        char arr[20]="you are very special";
        
        //send it to C1
        write(fd1[1],arr,strlen(arr));
        
        //read from C2
        read(fd3[0],arr,20);
        
        //show final string
        printf("%s","Final String in Parent Process: ");
        printf("%s",arr);
        printf("%c",'\n');
        
        wait(NULL);
        
    }
    else
    {
        if(fork())
        {
                // random number generator
                srand(time(0)+getpid());
                
                //closing pipes
                close(fd1[1]); // dont need to write to P
                close(fd2[0]); // dont need to read from C2
                close(fd3[0]); // f3 only used between P,C2
                close(fd3[1]); // f3 only used between P,C2
                
                // FOR C1
                
                //read from parent
                char arr[100];
                read(fd1[0],arr,100);
                
                //random number generated(from 1 to 5 to see how many characters to change)
                int randnum = (rand() % 5)+1;
            
                //random places to make these changes
                int *rnums = malloc(randnum);
                for(int i=0;i<randnum;i++)
                {
                    rnums[i]=(rand() % (strlen(arr)));
                }
                
                //make changes on origial array at these positions
                for(int i=0;i<randnum;i++)
                {
                    arr[rnums[i]]='x';
                }
                
                //display these changes
                printf("%s","After C1 Processing: ");
                printf("%s",arr);
                printf("%c",'\n');
                
                //write to C2
                write(fd2[1],arr,strlen(arr));
                
                //close remaining pipes
                close(fd2[1]);
                close(fd1[0]);
                
                wait(NULL);
                exit(0);
        }
        else
        {
                // random number generator
                srand(time(0)+getpid());
                
                //closing pipes
                close(fd1[1]); // f1 only used between P,C1
                close(fd1[0]); // f1 only used between P,C1
                close(fd2[1]); // dont need to write C1
                close(fd3[0]); // dont need to read from P

                //read from parent
                char arr[100];
                read(fd2[0],arr,100);
                
                // FOR C2
                //random number generated(from 1 to 5 to see how many characters to change)
                int randnum_c2 = (rand() % 5)+1;
            
                //random places to make these changes
                int *rnums_c2 = malloc(randnum_c2);
                for(int i=0;i<randnum_c2;i++)
                {
                    rnums_c2[i]=(rand() % (strlen(arr)));
                }
                
                //make changes on origial array at these positions
                for(int i=0;i<randnum_c2;i++)
                {
                    arr[rnums_c2[i]]='x';
                }
                
                //display these changes
                printf("%s","After C2 Processing: ");
                printf("%s",arr);
                printf("%c",'\n');
                
                //Writing from P
                write(fd3[1],arr,strlen(arr));
                
                //close remaining pipes
                close(fd3[1]);
                close(fd2[0]);
                
                exit(0);
        }
        
    }
    
    return 0;
}

