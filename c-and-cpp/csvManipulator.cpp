//GH_UP_CPP_9
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;

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
        StringToNativeType::convert(inp.substr(pos, currentEnd - pos), value);
        tokens.push_back(value);
        pos = currentEnd + 1;
    }

    if (inp.length() != std::string::npos &&
        inp.length() != pos)
    {
        Type value;
        StringToNativeType::convert(inp.substr(pos), value);
        tokens.push_back(value);
    }

    return tokens;
}

class CsvRow
{
public:
    std::vector<std::string> m_colDataVec;
};
class CsvManipulator
{
private:
    std::vector<CsvRow> m_rows;
    std::string m_delimitter=";";

public:
    CsvManipulator(const std::string &strFileName)
    {
        std::ifstream csvFileStream(strFileName);

        std::string strRow;

        while (std::getline(csvFileStream, strRow))
        {
            CsvRow csvRow;

            Tokenizer<string> stringTok;

            for (auto token : stringTok.getTokens(strRow, m_delimitter))
            {
                csvRow.m_colDataVec.push_back(token);
            }

            m_rows.push_back(csvRow);
        }
    }

    void updateRecords(const std::string &strOutFileName)
    {
        std::ofstream m_csvFileStream(strOutFileName);

        for (auto &csvRow : m_rows)
            if (csvRow.m_colDataVec[1] == "10")
                csvRow.m_colDataVec[1] = "20";

        for (auto &csvRow : m_rows)
        {
            for (auto &colData : csvRow.m_colDataVec)
                m_csvFileStream << colData << m_delimitter;

            m_csvFileStream << '\n';
        }
    }
};

int main()
{
    int myNumber = -1;

    CsvManipulator csvManip("myCsv.txt");
    csvManip.updateRecords("myCsv2.txt");
}
