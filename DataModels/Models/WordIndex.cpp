#include "WordIndex.h"

void WordIndex::UpdateDocumentBase(const Config &config)
{
    std::size_t count = config.getFilesCount();
    /*auto f = [this , &config](int i)
            {
                std::ifstream file(config.getFile(i));
                if (file.is_open()) {
                    indexFile(&file , i);
                }
            };
            */
    ThreadPool threadPool(2);
    for(std::size_t i = 0; i < count; i++) {
        //futures.push_back(threadPool.enqueue(f,i));
    }
    //threadPool.wait_all();
}

void WordIndex::UpdateDocumentBase(const std::vector<std::string> &docs)
{
    /*
    auto f = [this]( const std::string *str , int i) //lambda for multithreading
            {
                std::stringstream file;
                file << (*str);
                indexFile(&file,i);
            };
            */

    for(std::size_t i = 0; i < docs.size(); i++) {
        //threadPool.add_task(f ,&(docs[i]) , i);
    }
    //threadPool.wait_all();
}

void WordIndex::indexFile(std::istream *file, int i)
{
    std::shared_ptr<int> docID = std::make_shared<int>(i);
    while (!(file->eof())) {
        std::string cache;
        (*file) >> cache;
        wordHandler(cache);
        if(cache.length() > 0) {
            mute.lock();
            auto ptr = &data[cache];
            (*ptr)[docID] += 1;
            mute.unlock();
        }
    }
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
            str = nullptr;
         }
    }
}

void WordIndex::answerFill(const std::string &word , std::map<int,int> &bite) const
{
    auto ptr = data.find(word);
    if(ptr != data.end()){
        auto counter = &ptr->second;
        for (auto count: *counter) {
            bite[*(count.first)] += count.second;
        }
    }
}