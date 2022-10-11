#pragma once
#include <iostream>
#include <map>
#include "Models/WordCounter.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "JSONWorkers/Request.h"
#include "JSONWorkers/Config.h"
#include "JSONWorkers/Answer.h"
#include "Models/WordIndex.h"
#include "ThreadPool/ThreadPoolI.h"
class Engine {
    Request request;
    Config config;
    Answer answer;
    WordIndex data;

    void setAnswer();
    void ranking(std::vector<answ::Answer> &arr) const;
public:

    Engine(const std::string config,const std::string request,const std::string answer);
    void work();

};


