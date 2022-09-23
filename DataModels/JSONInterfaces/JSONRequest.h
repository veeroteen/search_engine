#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
class JSONRequest : public JSONBase {


public:
    std::vector<std::vector<std::string>*> *requests;

    JSONRequest();
    ~JSONRequest();
    virtual void addRequest() = 0;

    void fillDict() override;
    void load();

    std::size_t requestsCount() const;

};

