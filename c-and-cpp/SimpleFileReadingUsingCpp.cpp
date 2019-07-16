#include<fstream>
#include<vector>
#include<string>
#include<iostream>

class CFileManipulation
{
	private:
		std::ifstream m_fileStream_;
	public:
		CFileManipulation(std::string p_fileName);
		~CFileManipulation();
		
        bool getline(std::string &pLine);
		std::vector<std::string> getEachLineInVector();
};



CFileManipulation::CFileManipulation(std::string p_fileName)
{
	m_fileStream_.open(p_fileName.c_str());	
	
	if(!m_fileStream_.is_open())
	std::cout<<"Error: Cannot open the file "<<p_fileName<<std::endl;
	else
	std::cout<<"File "<<p_fileName<<" has been opened! "<<p_fileName<<std::endl;
}


CFileManipulation::~CFileManipulation()
{
	if(m_fileStream_.is_open())
	m_fileStream_.close();	
}

bool CFileManipulation::getline(std::string &pLine)
{	
	return std::getline(m_fileStream_,pLine);
}

int main()
{
    CFileManipulation fileObj("Tokenizer.cpp");

    std::string line;
    while(fileObj.getline(line))
    {
        std::cout << line << std::endl;
    }
    return 0;
}
