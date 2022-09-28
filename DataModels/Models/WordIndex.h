#include <iostream>
#include <map>
#include "WordCounter.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "AnswerModel.h"
#include "../JSONWorkers/Config.h"
#pragma once
class WordIndex {
    std::map<std::string,std::vector<WordCounter>> data;

    void fill(const Config &config);
    void fill(const std::vector<std::string> &docs);
    void indexFile(std::istream *file, const int &i);

    void sort();
    void draw();

    void wordHandler(std::string &str) const;
    void addWord(std::vector<WordCounter> *ptr , std::shared_ptr<int> docID);

public:
    WordIndex() = default;

    void UpdateDocumentBase(const Config &config);
    void UpdateDocumentBase(const std::vector<std::string> &docs);
    void answerFill(std::string &word , std::map<int,int> &bite);

};
