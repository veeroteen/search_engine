#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
#include <vector>
#include "nlohmann/json.hpp"
#include <iostream>
class JSONConfig : public JSONBase {
private:
    int responseCount;
public:
    JSONConfig() = default;
    int getResponsesCount() const;
    void load(const std::string &str);
protected:
    std::vector <std::string> files;
};



