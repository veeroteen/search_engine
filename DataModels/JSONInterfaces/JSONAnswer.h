#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
#include <vector>
#include "../Models/AnswerModel.h"

class JSONAnswer : public JSONBase {

public:
    JSONAnswer() = default;
    ~JSONAnswer();
    void add(answ::AnswerModel *answer);
    void fillDict();
protected:
    std::vector<answ::AnswerModel*> answers;
};

