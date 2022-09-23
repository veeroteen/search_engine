#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>

class JSONBase {
public:
    nlohmann::json dict;

    JSONBase() = default;
    virtual void fillDict() = 0;
    void saveDict(const std::string &fileName);
    void openDict(const std::string &fileName);
};

