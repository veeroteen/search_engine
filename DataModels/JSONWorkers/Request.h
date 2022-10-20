#pragma once
#include "JSONInterfaces/JSONRequest.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

class Request : public JSONRequest {
    std::mutex mute;
public:
    Request() = default;
    Request(const std::string &str);
    ~Request() = default;
    const std::vector<std::string>* getWords( const std::size_t iterator) const;
    std::size_t getRequestsCount() const;

};

