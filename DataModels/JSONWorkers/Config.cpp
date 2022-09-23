#include "Config.h"

Config::Config(const std::string &str)
{
    load(str);
}
std::size_t Config::getFilesCount() const
{
    return filesCount;
}

const std::string Config::getFile(const std::size_t iterator)
{

    try {
        if(iterator > files.size() - 1)
        {
            throw;
        }
        return files[iterator];
    }
    catch(...)
    {
        std::cerr << "Request out of range\n";
        return nullptr;
    }
}
void Config::loadConfig(const std::string &str)
{
    load(str);
    filesCount = files.size();
}