#pragma once
#include <string>
#include <memory>
struct WordCounter
{
    std::shared_ptr<int> docID;
    int count;
    WordCounter(std::shared_ptr<int> docID){
        this->docID = docID;
        count = 1;
    }
    bool operator> (const WordCounter &counter) const
    {
        if (this->count > counter.count){
            return true;
        }
        return false;
    }
    bool operator< (const WordCounter &counter) const
    {
        if(this->count < counter.count){
            return true;
        }
        return false;
    }
};