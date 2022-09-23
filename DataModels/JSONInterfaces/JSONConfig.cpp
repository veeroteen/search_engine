#include "JSONConfig.h"

std::string JSONConfig::getName() const
{
    return config["name"];
}
std::string JSONConfig::getVersion() const
{
    return config["version"];
}
int JSONConfig::getResponseCount() const
{
    return config["max_responses"];
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