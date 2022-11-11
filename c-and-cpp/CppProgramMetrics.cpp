
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/resource.h>

/* ================ Start of Metrics measurement code ==================*/

#define ELAPSED_TIME_B(myArgument) ElapsedTime myArgument;myArgument.start(std::string(__FUNCTION__)+std::string(" : ")+std::string(#myArgument));

#define ELAPSED_TIME_E(myArgument) myArgument.stop();



/*
Currently it is supported for linux, for others os it is not supported.
In order for easy copying to measure metrics, all class definitions are handled in single file
*/

///@brief Computation of elapsed time of program
class ElapsedTime
{
private:
    ///@brief Message for elapsed time
    std::string m_startMsg;

    ///@brief   convertToReqUnit
    ///@return   None
    double convertToReqUnit()
    {
        switch (m_unit)
        {
        case Unit_t::SECONDS:
            return m_elapsedTime;

        case Unit_t::MILLISECONDS:
            return m_elapsedTime * 1000;
        }

        return -1;
    }

    std::string getUnitDesc()
    {
        switch (m_unit)
        {
        case Unit_t::SECONDS:
            return "s";

        case Unit_t::MILLISECONDS:
            return "ms";
        }

        return "INVALID UNIT";
    }

public:
    ///@brief time point which holds the start and end time
    std::chrono::time_point<std::chrono::steady_clock> begin, end;

    enum class Unit_t
    {
        SECONDS = 0,
        MILLISECONDS,
    };

    ///@brief elapsed time
    double m_elapsedTime;

    ///@brief unit
    Unit_t m_unit = Unit_t::MILLISECONDS;

    ///@brief    start capturing elapsed time
    ///@return   None
    void start()
    {
        m_elapsedTime = 0;
        begin = std::chrono::steady_clock::now();
    }

    ///@brief    start capturing elapsed time and accumulated with previous metrics
    ///@param ArgName : ArgDesc
    ///@return   None
    void startAccumulate(const std::string &s)
    {
        m_startMsg = s;
        begin = std::chrono::steady_clock::now();
    }

    ///@brief    start capturing elapsed time
    ///@param string : message to display at end
    ///@return   None
    void start(const std::string &s)
    {
        m_startMsg = s;
        start();
    }

    ///@brief    constructor
    ElapsedTime()
    {
        start();
        m_elapsedTime = 0;
    }

    ///@brief    print the elapsed time
    ///@return   None
    void printTime()
    {
        std::cout << std::fixed << "Elapsed time[" << m_startMsg << "](" << getUnitDesc() << "): " << convertToReqUnit() << '\n';
    }

    ///@brief    stop capturing elapsed time and print values
    ///@return   None
    double stop()
    {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeTaken = end - begin;

        m_elapsedTime += timeTaken.count();

        printTime();

        return convertToReqUnit();
    }

    ///@brief    stopAccumulate the elapsed time and print values
    ///@return   None
    void stopAccumulate()
    {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeTaken = end - begin;
        m_elapsedTime += timeTaken.count();
    }

    ///@brief    destructor
    ~ElapsedTime()
    {
    }
};

class CppMemoryMetrics
{
public:
    // Returns the peak memory usage so far in bytes
    size_t getPeakMemoryUsageInBytes()
    {
        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);
        // rusage.ru_maxrss returns in KB, so coverting to bytes
        return (size_t)(rusage.ru_maxrss * 1024L);
    }

    void printMemoryUsageInKb()
    {
        // V6P - change to macro
        std::cout << "Memory usage(KB): " << getPeakMemoryUsageInBytes() / 1024 << std::endl;
    }
};

///@brief Calculation of CPU related metrics of the program
class CppCpuMetrics
{
private:
    ///@brief resource usage
    struct rusage cpuResUsage;

    ///@brief start and end time of cpu
    double m_endCpuTime;

    ///@brief is thread cpu time
    bool m_isThreadCpuTime = false;

    ///@brief total cpu time
    long double m_totalCpuTime;

    ///@brief starting user cpu time
    long double m_startUserCpuTime = 0;

    ///@brief starting system cpu time
    long double m_startSysCpuTime = 0;

    ///@brief user cpu time
    long double m_userCpuTime = 0;

    ///@brief  system cpu time
    long double m_sysCpuTime = 0;

    ///@brief message to display
    std::string m_descriptionStr;

    const int numberOfMicroSecInSec = 1000000;

    ///@brief   convertToReqUnit
    ///@return   None
    long double convertToReqUnit(const long double &dNumber)
    {
        switch (m_unit)
        {
        case Unit_t::SECONDS:
            return dNumber;

        case Unit_t::MILLISECONDS:
            return dNumber * 1000;
        }

        return -1;
    }

    std::string getUnitDesc()
    {
        switch (m_unit)
        {
        case Unit_t::SECONDS:
            return "s";

        case Unit_t::MILLISECONDS:
            return "ms";
        }

        return "INVALID UNIT";
    }

public:
    ///@brief    constructor
    ///@isThreadCpu - In case of multithreading and if we want to measure CPU consumed by current thread alone this has to be set as true
    ///@return   None
    CppCpuMetrics(const bool &isThreadCpu = false) : m_isThreadCpuTime(isThreadCpu)
    {
        m_endCpuTime = 0;
        m_totalCpuTime = 0;
    }

    enum class Unit_t
    {
        SECONDS = 0,
        MILLISECONDS,
    };

    ///@brief unit
    Unit_t m_unit = Unit_t::MILLISECONDS;

    ///@brief    Returns user cpu time from beginning of program to this point
    ///@return   double
    double getUserCpuTimeInSeconds()
    {
        getrusage(m_isThreadCpuTime ? RUSAGE_THREAD : RUSAGE_SELF, &cpuResUsage);
        // tv_usec is microseconds, so dividing by 1000000
        m_userCpuTime = convertToReqUnit(cpuResUsage.ru_utime.tv_sec + (cpuResUsage.ru_utime.tv_usec / static_cast<double>(numberOfMicroSecInSec))) - m_startUserCpuTime;

        return m_userCpuTime;
    }

    ///@brief    print the user cpu time
    ///@return   None
    void printUserCpuTimeInSeconds()
    {
        std::cout << "User CPU time(" << getUnitDesc() << "): " << getUserCpuTimeInSeconds() << '\n';
    }

    ///@brief    Returns system cpu time from beginning of program to this point
    ///@return   double
    double getSystemCpuTimeInSeconds()
    {

        getrusage(m_isThreadCpuTime ? RUSAGE_THREAD : RUSAGE_SELF, &cpuResUsage);
        // tv_usec is microseconds, so dividing by 1000000
        m_sysCpuTime = convertToReqUnit(cpuResUsage.ru_stime.tv_sec + (cpuResUsage.ru_stime.tv_usec / static_cast<double>(numberOfMicroSecInSec))) - m_startSysCpuTime;

        return m_sysCpuTime;
    }

    ///@brief    printSystemCpuTimeInSeconds
    ///@return   None
    void printSystemCpuTimeInSeconds()
    {
        std::cout << "System CPU time(" << getUnitDesc() << "): " << getSystemCpuTimeInSeconds() << '\n';
    }

    ///@brief    Starts the cpu time when this function is called
    ///@param descriptionStr : descriptionStr
    ///@return   None
    void start(const std::string &descriptionStr = "")
    {
        m_startUserCpuTime = getUserCpuTimeInSeconds();
        m_startSysCpuTime = getSystemCpuTimeInSeconds();

        m_descriptionStr = descriptionStr;
        m_endCpuTime = 0;
        m_sysCpuTime = 0;
        m_sysCpuTime = 0;
    }

    ///@brief    stops the cpu time calculation when this function is called
    ///@return   None
    void stop()
    {
        m_endCpuTime = getUserCpuTimeInSeconds() + getSystemCpuTimeInSeconds();
        std::cout << "CPU Time [ " << m_descriptionStr << " ] : " << m_endCpuTime << " " << getUnitDesc() << '\n';
    }
};

class CppProgramMetrics
{
private:
    ElapsedTime elapsedObj;
    CppCpuMetrics cpuMetrics;
    CppMemoryMetrics memMetrics;

public:
    CppProgramMetrics()
    {
    }

    void start(std::string metricsName)
    {
        elapsedObj.start(metricsName);
        cpuMetrics.start(metricsName);
    }

    void stop()
    {
        elapsedObj.stop();
        cpuMetrics.stop();
        memMetrics.printMemoryUsageInKb();
    }
};

/* ================ End of Metrics measurement code ==================*/

void elapsedTimeDemo()
{
    ElapsedTime elapTime;
    elapTime.start("Demo");
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    elapTime.stop();

    ElapsedTime elapTimeAcc;
    elapTimeAcc.startAccumulate("Demo Acc");
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    elapTimeAcc.stopAccumulate();

    elapTimeAcc.startAccumulate("Demo Acc");
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    elapTimeAcc.stopAccumulate();

    elapTimeAcc.printTime();
}

void cpuMetricsDemo()
{
    CppCpuMetrics cpuMetrics;
    cpuMetrics.start("CpuMetrics");

    CppProgramMetrics mainPgmMetrics;
    mainPgmMetrics.start("ProgramMetrics");

    {
        // Main code goes here
    }

    mainPgmMetrics.stop();

    int sum = 0;
    std::string s = "Hai";
    for (int i = 0; i < 1000000; i++)
    {
        sum = sum + i;
        s += "HELLO";
    }

    std::cout << sum << '\n';

    cpuMetrics.stop();
}

inline void elapsedTimeWithMacroDemo()
{
ELAPSED_TIME_B(L379);
std::this_thread::sleep_for(std::chrono::microseconds(1000));
ELAPSED_TIME_E(L379);


ELAPSED_TIME_B(L385);
std::this_thread::sleep_for(std::chrono::microseconds(1000));
ELAPSED_TIME_E(L385);

}

// Driver function
int main()
{
    elapsedTimeDemo();
    cpuMetricsDemo();
    elapsedTimeWithMacroDemo();

}
