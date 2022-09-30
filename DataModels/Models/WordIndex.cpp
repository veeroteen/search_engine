#include "WordIndex.h"

void WordIndex::fill(const Config &config)
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
    for(int i = 0; i < count; i++) {
        threads.emplace_back(new std::thread(f,i));
    }
    for(int i = 0; i < threads.size(); i++)
    {
        threads[i]->join();
    }
    draw();

}

void WordIndex::fill(const std::vector<std::string> &docs)
{

    std::vector<std::thread*> threads;
    auto f = [this]( const std::string *str , int i)
            {
                std::stringstream file;
                file << (*str);
                indexFile(&file,i);
            };
    for(int i = 0; i < docs.size(); i++) {
        threads.emplace_back(new std::thread(f ,&(docs[i]) , i));
    }
    for(int i = 0; i < threads.size(); i++)
    {
        threads[i]->join();
    }
    draw();

}

void WordIndex::indexFile(std::istream *file, int i)
{
    std::shared_ptr<int> docID = std::make_shared<int>(i);
    while (!(file->eof())) {
        std::string cache;
        (*file) >> cache;
        wordHandler(cache);
        auto ptr = &data[cache];
        addWord(ptr, docID);
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
void WordIndex::addWord(std::map<std::shared_ptr<int>, int> *ptr , std::shared_ptr<int> docID)
{
    mute.lock();
    (*ptr)[docID] += 1;
    mute.unlock();
}


void WordIndex::UpdateDocumentBase(const Config &config)
{
    fill(config);
}

void WordIndex::UpdateDocumentBase(const std::vector<std::string> &docs)
{
    fill(docs);
}

void WordIndex::answerFill(std::string &word , std::map<int,int> &bite)
{
    answ::Answer buff;
    auto ptr = &data[word];
    for(auto counter : *ptr)
    {
        bite[*(counter.first)] += counter.second;
    }
}