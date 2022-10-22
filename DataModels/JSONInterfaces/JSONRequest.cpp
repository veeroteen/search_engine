#include "JSONRequest.h"

JSONRequest::JSONRequest()
{
    requests = new  std::vector<std::vector<std::string>*>;
}
JSONRequest::~JSONRequest()
{
    for(int i = requests->size()-1; i >=0; i--)
    {
        if((*requests)[i] != nullptr) {
            delete (*requests)[i];
        }
    }
    if(requests != nullptr)
    {
        delete requests;
    }
}

void JSONRequest::loadRequests(const std::string &str)
{
    openDict(str);
    std::vector<std::string> rawRequests = dict["requests"];
    for(auto i : rawRequests)
    {
        auto *arr = new std::vector<std::string>;
        std::stringstream stream;
        stream << i;
        while(!stream.eof()){
            std::string buffer;
            stream >> buffer;
            arr->push_back(buffer);
        }
        requests->push_back(arr);
    }
    dict.clear();
}

std::size_t JSONRequest::requestsCount() const
{
    return requests->size();
}