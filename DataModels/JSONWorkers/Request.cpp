#include "Request.h"

Request::Request(const std::string &str) {
    loadRequests(str);
}


const std::vector<std::string>* Request::getWords( const std::size_t iterator)
{
    if(iterator > requests->size() - 1)
    {
        return nullptr;
    }
    words = (*requests)[iterator];
    return words;
}

void Request::loadRequests(const std::string &str)
{
    openDict(str);
    load();
}

std::size_t Request::getRequestsCount() const
{
    return requestsCount();
}
