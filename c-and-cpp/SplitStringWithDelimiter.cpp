#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::string;
using std::vector;

void demoFunction1()
{
    std::stringstream ss("1, withSpace , 2");
    vector<string> result;

    while (ss.good())
    {
        string substr;
        getline(ss, substr, ',');
        result.push_back(substr);
        cout << "substr :" << substr << '\n';

    }
}

int main()
{

    demoFunction1();

    return 0;
}
