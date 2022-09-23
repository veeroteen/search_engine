#pragma once
#include "../JSONInterfaces/JSONConfig.h"
#include <vector>
#include <string>
#include <iostream>

class Config : private JSONConfig{

    std::string file;
    int filesCount;
public:
    Config() = default;
    Config(const std::string &str);

    std::size_t getFilesCount() const;

    const std::string getFile(std::size_t iterator);
    void loadConfig(const std::string &str);

};



