#pragma once
#include "../JSONInterfaces/JSONAnswer.h"
#include <vector>
#include <string>
#include <iostream>
class Answer : private JSONAnswer {
    std::string fileName;

public:

    void addAnswer(std::vector<answ::Answer> &answer , int max_responses);
    void saveData();
    void setFileName(std::string fileName);
};


