#pragma once
#include "JSONInterfaces/JSONConfig.h"
#include <vector>
#include <string>
#include <iostream>

class Config : public JSONConfig{
    std::string file;
    int filesCount;
    int maxResponses;
public:
    Config() = default;
    Config(const std::string &str);
    ~Config() = default;
    std::size_t getFilesCount() const;

    //return filename by iterator
    const std::string getFile(std::size_t iterator) const;
    void loadConfig(const std::string &str);

};



