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
    if(fork())
    {
        if(fork())
        {
            cout<<"H5"<<endl;
            wait(NULL);
            wait(NULL);
        }
        else
        {
            if(fork())
            {
                if(fork())
                {
                    cout<<"H3"<<endl;
                    wait(NULL);
                    wait(NULL);
                }
                else
                {
                    cout<<"H2"<<endl;
                    exit(0);
                }
            }
            else
            {
                cout<<"H1"<<endl;
                exit(0);
            }
        }
    }
    else
    {
        cout<<"H4"<<endl;
        exit(0);
    }

    return 0;
}
