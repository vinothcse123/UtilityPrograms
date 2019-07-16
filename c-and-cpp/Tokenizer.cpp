#include <vector>
#include <string>
#include <iostream>

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
        tokens.push_back(inp.substr(pos, currentEnd - pos));
        pos = currentEnd + 1;
    }

    if (inp.length() != std::string::npos &&
        inp.length() != pos)
        tokens.push_back(inp.substr(pos));

    return tokens;
}

int main()
{
    using namespace std;

    Tokenizer<string> tok;

    for (auto token : tok.getTokens("HAI|HELLO|HEE|", "|"))
    {
        std::cout << token << std::endl;
    }
}
