#pragma once
#include "../JSONInterfaces/JSONAnswer.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
class Answer : private JSONAnswer {
    std::string fileName;
    std::mutex mute;
public:

    void addAnswer(std::vector<answ::Answer> &answer , std::size_t max_responses, int requestID);
    void saveData();
    void setFileName(std::string fileName);
};


