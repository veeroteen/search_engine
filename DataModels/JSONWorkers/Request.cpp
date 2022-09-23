#include "Request.h"

Request::Request(const std::string &str) {
    loadRequests(str);
}

void Request::addRequest()
{
    words = new std::vector<std::string>;
    std::cout << "Enter word, or 0 to end\n";
    while(true)
    {
        std::string str;
        std::cin >>
        str;
        if(str[0] != '0')
        {
            words->
            push_back(str);
        }
        else
        {
            break;
        }
    }
    requests->push_back(words);
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
