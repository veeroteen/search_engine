#pragma once
#include "JSONInterfaces/JSONAnswer.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
class Answer : public JSONAnswer {
    std::string fileName;

public:
    ~Answer() = default;

    void saveData();
    void setFileName(std::string fileName);
};


