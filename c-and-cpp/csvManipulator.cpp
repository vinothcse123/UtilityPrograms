//GH_UP_CPP_9
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

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
    std::string m_delimitter=",";
    CsvRow m_headerRow;
    int m_columnCount=0;
    bool m_isHeaderPresent=false;

public:
    CsvManipulator(const std::string &strFileName,bool isHeaderPresent=false)
    {
        std::ifstream csvFileStream(strFileName);
        bool isFirstRow=true;
        m_isHeaderPresent=isHeaderPresent;

        std::string strRow;

        while (std::getline(csvFileStream, strRow))
        {
            CsvRow csvRow;

            Tokenizer<string> stringTok;

            for (auto token : stringTok.getTokens(strRow, m_delimitter))
            {
                if(isHeaderPresent && isFirstRow)
                    m_headerRow.m_colDataVec.push_back(token);
                else
                    csvRow.m_colDataVec.push_back(token);
            }
            
            if(isHeaderPresent && isFirstRow)
                m_columnCount=m_headerRow.m_colDataVec.size();
            else if(isHeaderPresent)
                m_columnCount=csvRow.m_colDataVec.size();
            
            if(!isFirstRow)
                if(m_columnCount != csvRow.m_colDataVec.size())
                    throw std::runtime_error("Column count mismatch");
            
            if(!(isHeaderPresent && isFirstRow))
                m_rows.push_back(csvRow);
                
            isFirstRow=false;
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

    CsvRow getRowBasedOnKey(int searchColumnId,std::string strSearchKey)
    {


        if(searchColumnId > m_columnCount)
            throw std::runtime_error("getRowBasedOnKey: Search column id Total column count");

        for (auto &csvRow : m_rows)
        {

            if(csvRow.m_colDataVec.at(searchColumnId) == strSearchKey)
                return csvRow;
        }

        if(searchColumnId > m_columnCount)
            throw std::runtime_error("getRowBasedOnKey: Row not found");

    }

    int getColumnIndexByHeaderName(string strHeaderName)
    {
        if(!m_isHeaderPresent)
            throw std::runtime_error("Header is not enabled");
 
        for(int columnIndex=0; columnIndex<m_columnCount; columnIndex++)
            if(strHeaderName == m_headerRow.m_colDataVec.at(columnIndex))
                return columnIndex;

        throw std::runtime_error("Column header not found");
    }
};

void readAndUpdateCsvFile()
{
    CsvManipulator csvManip("myCsv.txt");
    csvManip.updateRecords("myCsv2.txt");
}


void getCsvRowBasedOnSearchKey()
{
    CsvManipulator csvManip("myCsv.txt",true);
    CsvRow searchRow = csvManip.getRowBasedOnKey(csvManip.getColumnIndexByHeaderName("COL1"),"37");
    std::cout << " searchRow.m_colDataVec[1] "<<  searchRow.m_colDataVec.at(1)  << "|" << std::endl;
}

int main()
{
    // readAndUpdateCsvFile();

    getCsvRowBasedOnSearchKey();


}
