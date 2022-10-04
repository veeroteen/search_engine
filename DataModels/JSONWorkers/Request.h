#pragma once
#include "../JSONInterfaces/JSONRequest.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

class Request : private JSONRequest {
    std::mutex mute;
public:
    Request() = default;

    Request(const std::string &str);

    const std::vector<std::string>* getWords( const std::size_t iterator) const;
    void loadRequests(const std::string &str);
    std::size_t getRequestsCount() const;

};

