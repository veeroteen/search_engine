#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
#include <vector>
#include "../Models/AnswerModel.h"

class JSONAnswer : public JSONBase {
    std::mutex mute;
public:
    JSONAnswer() = default;
    ~JSONAnswer();
    void add(answ::AnswerModel *answer);
    void fillDict();
    void addAnswer(std::vector<answ::Answer> &answer , std::size_t max_responses, int requestID);
protected:
    std::vector<answ::AnswerModel*> answers;
};

