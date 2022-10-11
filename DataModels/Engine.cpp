#include "Engine.h"


Engine::Engine(const std::string config,const std::string request,const std::string answer)
{
    this->request.loadRequests(request);
    this->config.loadConfig(config);
    this->answer.setFileName(answer);
}



void Engine::work()
{
    data.UpdateDocumentBase(config);
    setAnswer();
}

void Engine::setAnswer()
{
    std::size_t count = request.getRequestsCount();
    auto f = [this](int i) {
        auto words = request.getWords(i);
        std::map<int, int> bite;
        for (auto word: *words) {
            data.answerFill(word, bite);
        }
        std::vector<answ::Answer> arr;
        for (auto &ptr: bite) {
            arr.emplace_back(ptr.first, ptr.second);
        }
        ranking(arr);
        answer.addAnswer(arr, config.getResponsesCount(), i);
    };
    ThreadPoolI threadPool;
    for(int i = 0; i < count; i++)
    {
        threadPool.add_task( f,i);
    }
    threadPool.wait_all();
    //delete threadPool;
    answer.saveData();
}

void Engine::ranking(std::vector<answ::Answer> &arr) const
{
    std::sort(arr.begin(), arr.end() ,std::greater<answ::Answer>());
    if(arr.size() > 0) {
        float buff = arr[0].rank;
        for (int j = 0; j < arr.size(); j++) {
            arr[j].rank /= buff;
        }
    }
}




