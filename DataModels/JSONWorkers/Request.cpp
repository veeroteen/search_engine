#include "Request.h"

Request::Request(const std::string &str) {
    loadRequests(str);
}


const std::vector<std::string>* Request::getWords( const std::size_t iterator)
{
    try {
        if(iterator > requests->size() - 1)
        {
            throw;
        }
        words = (*requests)[iterator];
        return words;
    }
    catch(...)
    {
        std::cerr << "Request out of range\n";
        return nullptr;
    }
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
