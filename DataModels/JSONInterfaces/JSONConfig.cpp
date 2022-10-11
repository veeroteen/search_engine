#include "JSONConfig.h"


int JSONConfig::getResponsesCount() const
{
    return responseCount;
}

void JSONConfig::load(const std::string &str)
{
    openDict(str);
    responseCount = dict["config"]["max_responses"];
    files = std::vector<std::string>(dict["files"]);
}