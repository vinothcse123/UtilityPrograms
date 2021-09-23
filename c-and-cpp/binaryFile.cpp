//GH_UP_CPP_8

#include<iostream>
#include<fstream> 
#include <errno.h>


int writeAndReadBinaryFile()
{
   using namespace std;
   char buffer_char[100];
   string buffer_string;
   int32_t fileVersion=98,fileVersionRead=0;
   int32_t fileHeader1=76,fileHeader1Read=0;


      ofstream writeStream("binaryFile.binary");
      writeStream.write(reinterpret_cast<char*>(&fileVersion),sizeof(int32_t));
      writeStream.write(reinterpret_cast<char*>(&fileHeader1),sizeof(int32_t));

      writeStream.close();


      ifstream readStream("binaryFile.binary");
      readStream.read(reinterpret_cast<char*>(&fileVersionRead),sizeof(int32_t));
      readStream.read(reinterpret_cast<char*>(&fileHeader1Read),sizeof(int32_t));

      readStream.close();

    //   std::cout << "========V6P  fileVersionRead =========== "<<  fileVersionRead  << std::endl;
    //   std::cout << "========V6P  fileHeader1Read =========== "<<  fileHeader1Read  << std::endl;



   return 0;
}



int updatePartOfBinaryFile()
{
   using namespace std;
   char buffer_char[100];
   string buffer_string;
   int32_t fileVersion=98,fileVersionRead=0;
   int32_t fileHeader1=76,fileHeader1Read=0;


      ofstream writeStream("binaryFile.binary");
      writeStream.write(reinterpret_cast<char*>(&fileVersion),sizeof(int32_t));
      writeStream.write(reinterpret_cast<char*>(&fileHeader1),sizeof(int32_t));

      writeStream.close();

      //For updating part of file we should open in read mode and write mode. If we open only in write mode existing content is destroyed.
    
   int32_t updatedFileVersion=85,updatedFileVersionRead=0;


      fstream updateStream("binaryFile.binary",ios::in | ios::out | ios::binary);
      updateStream.write(reinterpret_cast<char*>(&updatedFileVersion),sizeof(int32_t));

      updateStream.close();


      //Reading again

      ifstream readStream("binaryFile.binary");
      readStream.read(reinterpret_cast<char*>(&updatedFileVersionRead),sizeof(int32_t));
      readStream.read(reinterpret_cast<char*>(&fileHeader1Read),sizeof(int32_t));

      readStream.close();

      std::cout << "========V6P  updatedFileVersionRead =========== "<<  updatedFileVersionRead  << std::endl;
      std::cout << "========V6P  fileHeader1Read =========== "<<  fileHeader1Read  << std::endl;



   return 0;
}

int main()
{
    writeAndReadBinaryFile();
    updatePartOfBinaryFile();
}
