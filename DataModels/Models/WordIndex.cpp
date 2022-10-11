#include "WordIndex.h"

void WordIndex::UpdateDocumentBase(const Config &config)
{

    std::size_t count = config.getFilesCount();
    std::vector<std::thread*> threads;
    auto f = [this , &config](int i)
            {
                std::ifstream file(config.getFile(i));
                if (file.is_open()) {
                    indexFile(&file , i);
                }
            };
    ThreadPoolI threadPool;
    for(int i = 0; i < count; i++) {
        threadPool.add_task(f,i);
    }
    threadPool.wait_all();
}

void WordIndex::UpdateDocumentBase(const std::vector<std::string> &docs)
{

    std::vector<std::thread*> threads;
    auto f = [this]( const std::string *str , int i)
            {
                std::stringstream file;
                file << (*str);
                indexFile(&file,i);
            };
    ThreadPoolI threadPool;
    for(int i = 0; i < docs.size(); i++) {
        threadPool.add_task(f ,&(docs[i]) , i);
    }
    threadPool.wait_all();
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

void WordIndex::draw(){
    for(auto i : data){

        std::cout << i.first << " : " << std::endl;
        for(auto j : i.second){
            std::cout << "          " << *(j.first) << " - " << j.second << std::endl;
        }
    }
}

void WordIndex::wordHandler(std::string &str) const
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] <= 'Z' && str[i] >= 'A')
        {
            str[i] +=32;
            continue;
        }
        if(str[i] < 'a' || str[i] > 'z')
        {
            str.erase(i, 1);
            i--;
        }
    }
}

void WordIndex::answerFill(std::string &word , std::map<int,int> &bite)
{
    answ::Answer buff;
    mute.lock();
    auto ptr = &data[word];
    mute.unlock();
    for(auto counter : *ptr)
    {
        bite[*(counter.first)] += counter.second;
    }
}