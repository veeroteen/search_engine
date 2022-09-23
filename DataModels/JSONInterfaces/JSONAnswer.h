#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
#include <vector>
#include "../Models/AnswerModel.h"

class JSONAnswer : public JSONBase {

public:
    std::vector<answ::AnswerModel*> answers;
    JSONAnswer() = default;
    ~JSONAnswer();
    void add(answ::AnswerModel *answer);
    void fillDict() override;
    void save(const std::string &string);

};

