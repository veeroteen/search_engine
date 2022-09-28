#include "WordIndex.h"

void WordIndex::fill(const Config &config)
{
    std::size_t count = config.getFilesCount();
    for(int i = 0; i < count; i++) {
        std::ifstream file(config.getFile(i));
        if (file.is_open()) {
            indexFile(&file, i);
        }
    }
    sort();
    draw();
}

void WordIndex::fill(const std::vector<std::string> &docs)
{
    for(int i = 0; i < docs.size(); i++)
    {
        std::stringstream file;
        file << docs[i];
        indexFile(&file,i);
    }
    sort();
    draw();
}

void WordIndex::indexFile(std::istream *file, const int &i)
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

void WordIndex::sort()
{
    for(auto &i : data) {
        std::sort(i.second.begin(), i.second.end(), std::greater<WordCounter>());
    }
}

void WordIndex::draw(){
    for(auto i : data){

        std::cout << i.first << " : " << std::endl;
        for(auto j : i.second){
            std::cout << "          " << *(j.docID.get()) << " - " << j.count << std::endl;
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
void WordIndex::addWord(std::vector<WordCounter> *ptr , std::shared_ptr<int> docID)
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
        bite[*(counter.docID)] += counter.count;
    }
}