#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include "AnswerModel.h"
#include "../JSONWorkers/Config.h"
#include <thread>
#include <mutex>
#include "../../Threadpool/ThreadPool.h"
#pragma once
class WordIndex {
    std::map<std::string,std::map<int,int>> data;
    std::mutex mute;

    //add words from files to word dictionary


    // bring word to normal state(change uppercase letter to lower). set word null if word have unsupported symbol
    void wordHandler(std::string &str) const;


public:
    WordIndex() = default;

    //fill word dictionary, by files input
    void UpdateDocumentBase(const Config &config);
    void indexFile(std::vector<std::string> *words, int i);
    //fill word dictionary, by vector of texts

    //fill raw answer by word
    void answerFill( const std::string &word , std::map<int,int> &bite) const;

};
