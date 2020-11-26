#include<iostream>
#include<string>
#include<sstream>
#include<sstream>
#include <cstring>


template<typename T>
T getTypedDataFromBuffer(char * const buffer,const int64_t & qOffset)
{
    return *(reinterpret_cast<T*>(buffer+qOffset));
}

int main()
{	
	using namespace std;

    int myInt=100;
    double myDouble=19.78;

    char buffer[100];

    memcpy(buffer,&myInt,sizeof(int));
    memcpy(buffer+sizeof(int),&myDouble,sizeof(myDouble));



    
    std::cout<< "HELLO " << getTypedDataFromBuffer<int>(buffer,0) << " " << getTypedDataFromBuffer<double>(buffer,sizeof(int))  <<std::endl;
	
	return 0;
}
