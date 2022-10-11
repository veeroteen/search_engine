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
#include "../ThreadPool/ThreadPoolI.h"
#pragma once
class WordIndex {
    std::map<std::string,std::map<std::shared_ptr<int>,int>> data;
    std::mutex mute;
    void indexFile(std::istream *file, int i);

    void draw();

    void wordHandler(std::string &str) const;
    void addWord(std::map<std::shared_ptr<int>, int> *ptr , std::shared_ptr<int> docID);

public:
    WordIndex() = default;

    void UpdateDocumentBase(const Config &config);
    void UpdateDocumentBase(const std::vector<std::string> &docs);
    void answerFill(std::string &word , std::map<int,int> &bite);

};
