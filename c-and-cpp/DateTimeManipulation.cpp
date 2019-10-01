
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

	void resetTime()
	{
		m_rawTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void printDateTime()
	{
		std::cout << ctime(&m_rawTime) << std::endl;
	}

	std::string printDateTimeWithUnderscore()
	{
		struct tm * timeinfo;
		timeinfo = localtime(&m_rawTime);
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
		return std::string(buffer);
	}
};

int main()
{
	DateTimeManipulation obj;
	obj.printDateTime();
}
