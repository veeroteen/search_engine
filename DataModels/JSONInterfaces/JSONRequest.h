#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
class JSONRequest : public JSONBase {


public:
    std::vector<std::vector<std::string>*> *requests;

    JSONRequest();
    ~JSONRequest();

    void fillDict() override;
    void load();

    std::size_t requestsCount() const;

};

