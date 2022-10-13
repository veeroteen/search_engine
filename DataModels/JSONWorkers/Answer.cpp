#include "Answer.h"

void Answer::addAnswer(std::vector<answ::Answer> &answer , std::size_t max_responses , int requestID)
{
    auto buff = new answ::AnswerModel();
    buff->requestID = requestID;
    for (std::size_t i = 0; i < max_responses && i < answer.size(); i++) {
        buff->addAnswer(answer[i]);
    }
    mute.lock();
    add(buff);
    mute.unlock();
}
void Answer::saveData()
{
    fillDict();
    saveDict(fileName);
}
void Answer::setFileName(std::string fileName)
{
    this->fileName = fileName;
}