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
#include "../Threadpool/ThreadPool.h"
//main class of app
class Engine {
    Request request;
    Config config;
    Answer answer;
    WordIndex data;

    //generate answer file from "answer"
    void setAnswer();

    void ranking(std::vector<answ::Answer> &arr) const;
public:

    //load app settings from json fle
    Engine(const std::string config,const std::string request,const std::string answer);

    void work();
};


