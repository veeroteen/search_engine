#include "Answer.h"

void Answer::addAnswer(std::vector<answ::Answer> &answer , int max_responses)
{
    if(answer.size() != 0) {
        auto buff = new answ::AnswerModel();
        for (std::size_t i = 0; i < max_responses && i < answer.size(); i++) {
            buff->addAnswer(answer[i]);

        }
        add(buff);
    }
    else
    {
        add(new answ::AnswerModel());
    }
}
void Answer::saveData()
{
    fillDict();
    save(fileName);
}
void Answer::setFileName(std::string fileName)
{
    this->fileName = fileName;
}