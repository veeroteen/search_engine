#pragma once
#include "JSONBase.h"
#include <string>
#include <sstream>
class JSONRequest : public JSONBase {
public:

    JSONRequest();
    ~JSONRequest();

    void load(const std::string &str);
    std::size_t requestsCount() const;
protected:
    std::vector<std::vector<std::string>*> *requests;
};

