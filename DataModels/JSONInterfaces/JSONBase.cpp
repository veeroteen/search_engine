#include "JSONBase.h"

void JSONBase::saveDict(const std::string &fileName)
{
    std::ofstream file( fileName);
    file << std::setw(4) << dict;
    file.close();
}
void JSONBase::openDict(const std::string &fileName)
{
    std::ifstream file(fileName);
    if(file.is_open()) {
        file >> dict;
    }
    file.close();
}