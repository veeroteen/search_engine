#include "JSONConfig.h"


int JSONConfig::getResponsesCount() const
{
    return responseCount;
}

void JSONConfig::load(const std::string &str)
{
    openDict(str);
    if(dict.begin() == dict.end())
    {
        openDict("../Configs/config.json");
        saveDict( str);
        auto buff = std::vector<std::string>(dict["files"]);
        for(auto i: buff)
        {
            std::ofstream output(i);
            std::ifstream input("../Configs/" + i);
            while(!input.eof())
            {
                std::string tmp;
                std::getline(input, tmp);
                output << tmp << std::endl;
            }
            input.close();
            output.close();
        }
    }
    responseCount = dict["config"]["max_responses"];
    files = std::vector<std::string>(dict["files"]);

    dict.clear();
}