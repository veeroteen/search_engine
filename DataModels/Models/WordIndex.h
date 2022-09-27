#include <iostream>
#include <map>
#include "WordCounter.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "AnswerModel.h"
#include "../JSONWorkers/Config.h"
class WordIndex {
    std::map<std::string,std::vector<WordCounter>> data;


    void fill(const Config &config)
    {
        std::size_t count = config.getFilesCount();
        for(int i = 0; i < count; i++) {
            std::ifstream file(config.getFile(i));
            if (file.is_open()) {
                std::shared_ptr<int> docID = std::make_shared<int>(i);
                while (!file.eof()) {
                    std::string cache;
                    file >> cache;
                    wordHandler(cache);
                    auto ptr = &data[cache];
                    addWord(ptr, docID);
                }
            }
        }
        sort();
        draw();
    }

    void sort()
    {
        for(auto &i : data) {
            std::sort(i.second.begin(), i.second.end(), std::greater<WordCounter>());
        }
    }

    void draw(){
        for(auto i : data){

            std::cout << i.first << " : " << std::endl;
            for(auto j : i.second){
                std::cout << "          " << *(j.docID.get()) << " - " << j.count << std::endl;
            }
        }
    }

    void wordHandler(std::string &str) const
    {
        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] < 91 && str[i] > 64)
            {
                str[i] +=32;
                continue;
            }
            if(str[i] < 97 && str[i] > 122)
            {
                str.erase(i, 1);
            }
        }
    }
    void addWord(std::vector<WordCounter> *ptr , std::shared_ptr<int> docID)
    {
        if (ptr->size() > 0)
        {
            auto j = ptr->end() - 1;
            if (j->docID == docID) {
                j->count++;
            } else {
                ptr->emplace_back(docID);
            }
        }
        else
        {
            ptr->emplace_back(docID);
        }

    }

public:
    void UpdateDocumentBase(const Config &config)
    {
        fill(config);
    }

    void answerFill(std::string &word , std::map<int,int> &bite)
    {
        answ::Answer buff;
        auto ptr = &data[word];
        for(auto counter : *ptr)
        {
            bite[*(counter.docID)] += counter.count;
        }
    }

};
