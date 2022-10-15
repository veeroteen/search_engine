#include <iostream>
#include <map>
#include "WordCounter.h"
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
    std::map<std::string,std::map<std::shared_ptr<int>,int>> data;
    std::mutex mute;

    //add words from files to word dictionary
    void indexFile(std::istream *file, int i);

    // bring word to normal state(change uppercase letter to lower). set word null if word have unsupported symbol
    void wordHandler(std::string &str) const;


public:
    WordIndex() = default;

    //fill word dictionary, by files input
    void UpdateDocumentBase(const Config &config);

    //fill word dictionary, by vector of texts
    void UpdateDocumentBase(const std::vector<std::string> &docs);

    //fill raw answer by word
    void answerFill( const std::string &word , std::map<int,int> &bite) const;

};
