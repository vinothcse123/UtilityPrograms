// GH_UP_CPP_6

#include <thread>
#include <iostream>
#include <future>
#include <mutex>


void threadModule(int myInput)
{
    std::cout << "Thread Id: " << std::this_thread::get_id() << std::endl;
    
    
}


void mulithreadUsingStandardThread()
{
    using namespace std;
    const int32_t dwThreadCount=3;
  

    std::thread threadArray[dwThreadCount];
    for (int i = 0; i < dwThreadCount; i++)
    {
        threadArray[i] = thread(&threadModule, 100);
    }

    for (int i = 0; i < dwThreadCount; i++)
    {
        threadArray[i].join();
    }

    std::cout << "All thread completed" << std::endl;
}

int main()
{
    mulithreadUsingStandardThread();
    return 0;
}
