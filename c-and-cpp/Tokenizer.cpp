#include <vector>
#include <string>
#include <iostream>

namespace StringToNativeType
{
    using std::string;

    template <typename T>
    inline void convert(string inputStr, T &value)
    {
        value = stoll(inputStr);
    }

    template <>
    inline void convert(string inputStr, string &value)
    {
        value = inputStr;
    }

    template <>
    inline void convert(string inputStr, double &value)
    {
        value = stod(inputStr);
    }

    template <>
    inline void convert(string inputStr, float &value)
    {
        value = stof(inputStr);
    }

} 

template <class Type>
class Tokenizer
{
public:
    Tokenizer(){};
    std::vector<Type> getTokens(const std::string &inp, const std::string &pDelimiter);
};

template <class Type>
std::vector<Type> Tokenizer<Type>::getTokens(const std::string &inp, const std::string &pDelimiter)
{
    using namespace std;
    vector<Type> tokens;
    size_t pos = 0, currentEnd = 0;

    while ((currentEnd = inp.find(pDelimiter, pos)) != std::string::npos)
    {
        Type value;
        StringToNativeType::convert(inp.substr(pos, currentEnd - pos),value);
        tokens.push_back(value);
        pos = currentEnd + 1;
    }

    if (inp.length() != std::string::npos &&
        inp.length() != pos)
        {
            Type value;
            StringToNativeType::convert(inp.substr(pos),value);
            tokens.push_back(value);
        }        

    return tokens;
}

int main()
{
    using namespace std;

    Tokenizer<string> stringTok;

    for (auto token : stringTok.getTokens("HAI|HELLO|HEE|", "|"))
    {
        std::cout << token << std::endl;
    }

    Tokenizer<int> intToken;

    for (auto token : stringTok.getTokens("5,6,10", ","))
    {
        std::cout << token << std::endl;
    }
}
