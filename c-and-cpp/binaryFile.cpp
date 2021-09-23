//GH_UP_CPP_8

#include<iostream>
#include<fstream> 
#include <errno.h>
int main()
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

      std::cout << "========V6P  fileVersionRead =========== "<<  fileVersionRead  << std::endl;
      std::cout << "========V6P  fileHeader1Read =========== "<<  fileHeader1Read  << std::endl;



   return 0;
}
