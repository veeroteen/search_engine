#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
#include <vector>
#include "nlohmann/json.hpp"
#include <iostream>
class JSONConfig : public JSONBase {
public:

    JSONConfig() = default;

    std::string getName() const;
    std::string getVersion() const;

    void fillDict() override;
    void load(const std::string &str);
protected:
    nlohmann::json config;
    std::vector <std::string> files;
};



