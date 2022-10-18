#include "WordIndex.h"

void WordIndex::UpdateDocumentBase(const Config &config) {
    size_t count = config.getFilesCount();
    std::vector<std::future<void>> futures;
    ThreadPool threadPool(2);
    for (size_t i = 0; i < count; i++) {
        std::ifstream file(config.getFile(i));
        std::vector<std::string> *words = new std::vector<std::string>;
        while (!file.eof()) {
            std::string word;
            file >> word;
            words->push_back(word);
        }
        futures.push_back(threadPool.enqueue(&WordIndex::indexFile, this, words, i));
    }
    for (auto &future: futures) {
        future.get();
    }
}
void WordIndex::indexFile(std::vector<std::string> *words, int i)
{
    int docID = i;
    for(auto word : *words) {
        wordHandler(word);
        if(word.length() > 0) {
            mute.lock();
            auto ptr = &data[word];
            (*ptr)[docID] += 1;
            mute.unlock();
        }
    }
    delete words;
}

void WordIndex::wordHandler(std::string &str) const
{
    for(std::size_t i = 0; i < str.length(); i++)
    {
        if(str[i] <= 'Z' && str[i] >= 'A')
        {
            str[i] +=32;
            continue;
        }
        if(str[i] < 'a' || str[i] > 'z')
        {
            str.erase(i,1);
        }
    }
}

void WordIndex::answerFill(const std::string &word , std::map<int,int> &bite) const
{
    auto ptr = data.find(word);
    if(ptr != data.end()){
        auto counter = &ptr->second;
        for (auto count: *counter) {
            bite[count.first] += count.second;
        }
    }
}