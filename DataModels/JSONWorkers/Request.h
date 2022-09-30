#pragma once
#include "../JSONInterfaces/JSONRequest.h"
#include <vector>
#include <string>
#include <iostream>
class Request : private JSONRequest {
    std::vector<std::string> *words;

public:
    Request() = default;

    Request(const std::string &str);


    const std::vector<std::string>* getWords( const std::size_t iterator);
    void loadRequests(const std::string &str);
    std::size_t getRequestsCount() const;

};

