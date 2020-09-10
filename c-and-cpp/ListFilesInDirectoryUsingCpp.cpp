
//g++ $1 -std=c++17  -lstdc++fs


#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    std::string path = "/RMS/nrsp/vinoth/playground";
    for (const auto & entry : fs::recursive_directory_iterator(path))
        std::cout << entry.path() << std::endl;
}
