#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int main()
{
    int fd1[2];
    int fd2[2];
    if(pipe(fd1)==-1)
    {
        printf("ERROR");
    }
    if(pipe(fd2)==-1)
    {
        printf("ERROR");
    }
    if(fork())
    {   
        close(fd1[0]);
        close(fd2[1]);
        while(1)
        {
            char this='a';
            char before='b';
            int sentence=0;
            while(1)
            {
                before=this;
                printf("%s","Enter Text: ");
                scanf ("%[^\n]%*c", &this);
                write(fd1[1],&this,1);
                
                if(this == '?' || this == '.' || this =='#')
                {
                    if(before != '/')
                    {
                        break;
                    }
                }
            }
            if(this == '?' || this == '.')
            {
                read(fd2[0],&sentence,4);
                printf("%s","Sentence Number ");
                printf("%i",sentence);
                printf("%s"," recieved by P2\n\n");
                sleep(1);
            }
            if(this == '#')
            {
                write(fd1[1],&this,1);
                printf("%s","P1 Exiting...");
                wait(NULL);
                break;
            }

        }
        close(fd1[1]);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);
        int i=1;
        while(1)
        {
            char arr[100];
            int index=0;
            char this;
            char before;
            while(1)
            {
                read(fd1[0],&this,1);
                arr[index]=this;
                index++;
                if(this == '?' || this == '.' || this =='#')
                {
                    if(before != '/')
                    {
                        arr[index]='\0';
                        break;
                    }
                    else
                    {
                        arr[index-2]=this;
                        index--;
                    }
                }
                before=this;
            }
            if(this=='#')
            {
                printf("%s","Incomplete Sentence Received\n");
                printf("%s","P2 Exiting...\n");
                break;
            }
            if(this == '?' || this == '.')
            {
                printf("%s","\nSentence Received: ");
                printf("%s",arr);
                printf("%c",'\n');
                write(fd2[1],&i,4);
                printf("%s","Sentence Number sent to P1\n");
                i++;
            }
            
        }
       
        close(fd1[0]);
        close(fd2[1]);
    }

    return 0;
}

