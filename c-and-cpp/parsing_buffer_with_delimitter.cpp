/* parsing or splitting a string buffer with delimiter */

#include<iostream>
#include "exploreme.h"
#include <sstream>
#include <vector>
#include <list>

template<class Type>
int splitDelimitedString(std::string &p_source_string,char p_delimiter,Type p_container)
{
   std::stringstream l_stringstream(p_source_string);
   std::string l_parsed_string;

   while( std::getline(l_stringstream,l_parsed_string,p_delimiter))
   {
      p_container.push_back(l_parsed_string);           
      std::cout << l_parsed_string <<"\n";
   }

   return 0;
}

int main()
{
   typedef  std::list<std::string> storageType_t;
   storageType_t  l_containter;
   std::string l_source_string("TEST1 TEST2 TEST3;+* /*/841 \n");
   splitDelimitedString<storageType_t >(l_source_string,' ',l_containter);

   return 0;
}
