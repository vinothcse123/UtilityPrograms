
#include <iostream>
#include <chrono>



class DateTimeManipulation
{
	time_t m_rawTime;



public:

	DateTimeManipulation()
	{
		m_rawTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void printDateTime()
	{
		std::cout << ctime(&m_rawTime) << std::endl;
	}
};

int main()
{
	DateTimeManipulation obj;
	obj.printDateTime();
}
