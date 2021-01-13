//GH_UP_CPP_2


#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::string;

void findAndReplace()
{
   string str="myFile.txt";
   string findstr=".txt";
   string replaceStr=".csv";
   int pos=0;
   pos=str.find(findstr,0); // Changes to -1
   cout<< "pos :" << pos << '\n';	

    str.replace(pos,findstr.length(),replaceStr);

    cout<< "str after replace : " << str << '\n';	

}

int main()
{
    findAndReplace();

   


    
    return 0;
}
