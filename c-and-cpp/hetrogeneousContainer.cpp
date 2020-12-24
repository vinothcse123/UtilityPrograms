
//UP_1 : Hetrogeneous container to store different Types like vector<int>, vector<double>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::string;
using std::vector;

class HetroElementBase
{
public:
    template <typename T>
    T& getSpecificType(); //!< Returns object of specific type T

};

template <typename T>
class HetroElement : public HetroElementBase
{
public:
    T m_hetroElement; //!< Element of specific data type
};

template <typename T>
T &HetroElementBase::getSpecificType()
{
    HetroElement<T> *pHetroElement = static_cast<HetroElement<T> *>(this);
    return pHetroElement->m_hetroElement;
}

int main()
{
    //Container which stores the objects of different type Eg: vector<int>, vector<double>
    vector<std::unique_ptr<HetroElementBase>> hetroContainerVec;

    //Pushing vector<int>
    hetroContainerVec.push_back(std::unique_ptr<HetroElementBase>(new HetroElement<vector<int>>));    

    //Pushing vector<double>
    hetroContainerVec.push_back(std::unique_ptr<HetroElementBase>(new HetroElement<vector<double>>));

    //Getting vector<int> from container
    vector<int> &intVec= hetroContainerVec[0]->getSpecificType<vector<int>>();
    intVec.push_back(100);

    //Getting vector<double> from container
    vector<double> &doubleVec= hetroContainerVec[1]->getSpecificType<vector<double>>();
    doubleVec.push_back(29.88);

    cout << "Result: vector<int> : " << intVec[0] << '\n';
    cout << "Result: vector<double> : " << doubleVec[0] << '\n';

    return 0;
}
