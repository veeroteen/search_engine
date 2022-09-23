#include "JSONAnswer.h"

JSONAnswer::~JSONAnswer()
{
    for(auto i : answers)
    {
        if(i != nullptr) {
            delete i;
        }
    }
}
void JSONAnswer::add(answ::AnswerModel *answer)
{
    answers.push_back(answer);
}
void JSONAnswer::fillDict()
{
    nlohmann::json buff;
    for(int i = 0; i < answers.size(); i++)
    {
        auto answer = answers[i];
        std::string str = "request";
        buff[str + std::to_string(i)] = answer->toDict();
    }
    dict["answers"] = buff;
}
void JSONAnswer::save(const std::string &string)
{
    saveDict(string);
}
