
#include <iostream>
#include<chrono>
#include <thread>

class ElapsedTime
{
private:
	std::string m_startMsg;	
public:

	std::chrono::time_point<std::chrono::steady_clock> begin,end;
	unsigned long int m_elapsedTime;
	

	void start()
	{
		m_elapsedTime=0;
		begin = std::chrono::steady_clock::now();
	}
	
	void startAccumulate(const std::string& s)
	{
		m_startMsg = s;
		begin = std::chrono::steady_clock::now();
	}

	void start(const std::string& s) { m_startMsg = s;  start(); }

	ElapsedTime() { start();  m_elapsedTime = 0; }

	void printTime() 
	{
		std::cout << "Elapsed Time [ "<< m_startMsg << " ]:" << m_elapsedTime <<  " microseconds" <<std::endl;		
	}

	void stop()
	{
		end = std::chrono::steady_clock::now();
		m_elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() ;
		std::cout << "Elapsed Time [ "<< m_startMsg << " ]:" << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() <<  " microseconds" <<std::endl;
	}
	
	void stopAccumulate()
	{
		end = std::chrono::steady_clock::now();
		m_elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() ;
	}


	~ElapsedTime()
	{
		
	}
};

int main()
{
	ElapsedTime obj;

	std::this_thread::sleep_for(std::chrono::milliseconds(40));
	
}

