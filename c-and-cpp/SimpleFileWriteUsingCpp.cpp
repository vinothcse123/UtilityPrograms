#include<fstream>
#include<vector>
#include<string>
#include<iostream>

class CFileWrite
{
	private:
		std::ofstream m_fileStream_;
	public:
		CFileWrite(std::string p_fileName);
		~CFileWrite();
		
        bool writeline(std::string &pLine);
};



CFileWrite::CFileWrite(std::string p_fileName)
{
	m_fileStream_.open(p_fileName.c_str());	
	
	if(!m_fileStream_.is_open())
	std::cout<<"Error: Cannot open the file "<<p_fileName<<std::endl;
	else
	std::cout<<"File "<<p_fileName<<" has been opened! "<<p_fileName<<std::endl;
}


CFileWrite::~CFileWrite()
{
	if(m_fileStream_.is_open())
	m_fileStream_.close();	
}

bool CFileWrite::writeline(std::string &pLine)
{	
	m_fileStream_ << pLine;
}

int main()
{
    CFileWrite fileObj("V6Write.txt");

    std::string line="HELLO";
    fileObj.writeline(line);
  
    return 0;
}
