#include "JSONBase.h"

void JSONBase::saveDict(const std::string &fileName)
{
    std::ofstream file(fileName);
    file << dict;
    file.close();
}
void JSONBase::openDict(const std::string &fileName)
{
    std::ifstream file(fileName);
    file >> dict;
    file.close();
}