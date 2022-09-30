#include "JSONConfig.h"

std::string JSONConfig::getName() const
{
    return config["name"];
}
std::string JSONConfig::getVersion() const
{
    return config["version"];
}

void JSONConfig::fillDict()
{
dict["config"] = config;
dict["files"] = files;
}
void JSONConfig::load(const std::string &str)
{
    openDict(str);
    config = dict["config"];
    files = std::vector<std::string>(dict["files"]);
}