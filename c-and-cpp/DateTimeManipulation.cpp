
// GH_UP_CPP_4

#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

using std::string;

class DateTimeManipulation
{
	time_t m_rawTime;

public:

    enum class Format_t
    {
        YYYYMMDDHHMMSS=1,
    };

	DateTimeManipulation()
	{
		m_rawTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

    DateTimeManipulation(const Format_t& format,const string& strDateTime)
	{
        std::tm timeInfo ={};

        switch(format)
        {
            case Format_t::YYYYMMDDHHMMSS:
            std::istringstream ss(strDateTime);
            ss >> std::get_time(&timeInfo, "%Y%m%d%H%M%S");

            if (!ss.fail())
                m_rawTime = mktime(&timeInfo);
            
            break;

        }


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
		strftime(buffer, sizeof(buffer), "%Y_%m_%d_%H_%M_%S", timeinfo);
		return std::string(buffer);
	}
};


void printCurrentDateTime()
{
    DateTimeManipulation obj;	
	std::cout << obj.printDateTimeWithUnderscore() << std::endl;
}


void convertStrintToDateTime()
{
    DateTimeManipulation obj(DateTimeManipulation::Format_t::YYYYMMDDHHMMSS,"20200130102010");
    std::cout << obj.printDateTimeWithUnderscore() << std::endl;
}

int main()
{
    printCurrentDateTime();
    convertStrintToDateTime();
	
}
