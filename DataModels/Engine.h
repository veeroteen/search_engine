#pragma once
#include <iostream>
#include <map>
#include "WordCounter.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "JSONWorkers/Request.h"
#include "JSONWorkers/Config.h"
#include "JSONWorkers/Answer.h"

class Engine {
    std::map<std::string,std::vector<WordCounter>> data;
    Request request;
    Config config;
    Answer answer;

public:
    Engine(const std::string config,const std::string request,const std::string answer);

    void work();

    void setAnswer();
    void answerFill(std::string &word , std::map<int,int> &bite);

    void wordHandler(std::string &str) const;
    void fill();
    void sort();
    void draw();

};


