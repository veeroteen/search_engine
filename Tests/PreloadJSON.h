#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../DataModels/Engine.h"
#include <fstream>
void setConfig(const std::string &fileName, const std::vector<std::string> &docs){
    nlohmann::json cfg;
    cfg["name"] = "TEST";
    cfg["version"] = 0;
    cfg["max_responses"] = 5;
    std::vector<std::string> fileNames;
    for(std::size_t i = 0; i < docs.size(); i++)
    {
        std::string buff = "testfile" + std::to_string(i) + ".txt";
        std::ofstream file(buff);
        file << docs[i];
        file.close();
        fileNames.push_back(buff);
    }
    nlohmann::json config;
    config["config"] = cfg;
    config["files"] = fileNames;
    std::ofstream file(fileName);
    file << config;
    file.close();

}
void setRequests(const std::string &fileName,const std::vector<std::string> &requests)
{
    nlohmann::json request;
    request["requests"] = requests;
    std::ofstream file(fileName);
    file << request;
    file.close();

}