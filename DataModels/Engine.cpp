#include "Engine.h"


Engine::Engine(const std::string config,const std::string request,const std::string answer)
{
    this->request.loadRequests(request);
    this->config.loadConfig(config);
    this->answer.setFileName(answer);
}

void Engine::wordHandler(std::string &str) const
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

void Engine::work()
{
    fill();
    setAnswer();
}

void Engine::setAnswer()
{
    std::size_t count = request.getRequestsCount();
    for(int i = 0; i < count; i++)
    {
        auto words = request.getWords(i);
        std::map<int,int> bite;
        for(auto word : *words)
        {
            answerFill(word,bite);
        }
        std::vector <answ::Answer> arr;
        for(auto &ptr : bite)
        {
            arr.emplace_back(ptr.first,ptr.second);
        }

        std::sort(arr.begin(), arr.end() ,std::greater<answ::Answer>());
        if(arr.size() > 0) {
            float buff = arr[0].rank;
            for (int j = 0; j < arr.size(); j++) {
                arr[j].rank /= buff;
            }
        }
        answer.addAnswer(arr, config.getFilesCount());
    }
    answer.saveData();
}

void Engine::answerFill(std::string &word , std::map<int,int> &bite)
{
    answ::Answer buff;
    auto ptr = &data[word];
    for(auto counter : *ptr)
    {
        bite[*(counter.docID)] += counter.count;
    }
}

void Engine::fill()
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
                if (ptr->size() > 0) {
                    auto j = ptr->end() - 1;
                    if (j->docID == docID) {
                        j->count++;
                    } else {
                        ptr->emplace_back(docID);
                    }
                } else {
                    ptr->emplace_back(docID);
                }
            }
        }
    }
    sort();
    draw();
}

void Engine::sort()
{
    for(auto &i : data) {
        std::sort(i.second.begin(), i.second.end(), std::greater<WordCounter>());
    }
}

void Engine::draw(){
    for(auto i : data){

        std::cout << i.first << " : " << std::endl;
        for(auto j : i.second){
            std::cout << "          " << *(j.docID.get()) << " - " << j.count << std::endl;
        }
    }
}
