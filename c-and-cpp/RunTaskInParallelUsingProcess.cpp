// GH_UP_CPP_7

#include <thread>
#include <iostream>
#include <future>
#include <mutex>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


void processModule()
{
    std::cout << "New Process " << std::endl;
    
    
}


void mulithreadUsingStandardThread()
{
    using namespace std;
    const int32_t dwThreadCount=3;
  

    for(int i=0;i<dwThreadCount;i++) 
    {
        if(fork() == 0)
        {
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            processModule();
            exit(0);
        }
    }
    for(int i=0;i<dwThreadCount;i++) 
    {
    wait(NULL); return ;
    }



    std::cout << "All Process completed" << endl;
}

int main()
{
    mulithreadUsingStandardThread();
    return 0;
}
