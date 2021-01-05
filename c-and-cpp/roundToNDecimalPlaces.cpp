//GH_UP_CPP_1

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include<sstream>

using std::vector;
using std::cout;
using std::string;

int main()
{
    long double myNumber=0.023605884365378037;

    long double m_multiplier=100;


    long double roundValue = std::round(myNumber * m_multiplier) / m_multiplier;

    
    cout<< "(myNumber * m_multiplier) :" << (myNumber * m_multiplier) << '\n';
    cout<< "std::ceil(myNumber * m_multiplier) :" << std::ceil(myNumber * m_multiplier) << '\n';
    cout<< "Result :" << roundValue << '\n';	
    return 0;
}
