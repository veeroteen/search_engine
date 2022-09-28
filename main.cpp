#include <iostream>
#include <vector>
#include "DataModels/Engine.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <random>
#include "DataModels/Models/WordIndex.h"
#include "gtest/gtest.h"
void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        std::vector<std::string>& requests,
        const std::vector<std::map<int,int>>& expected
) {
    std::vector<std::map<int,int>> result;
    WordIndex idx;
    idx.UpdateDocumentBase(docs);

    for(auto& request : requests) {
        std::map<int,int> bite;
        idx.answerFill(request,bite);
        result.push_back(bite);
    }
    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::map<int,int>> expected = {
            {
                    {0, 1}
            }, {
                    {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    std::vector<std::string> requests = {"milk", "water", "cappuchino"};
    const std::vector<std::map<int,int>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            }, {
                    {0, 2}, {1, 2}, {2, 5}
            }, {
                    {3, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const std::vector<std::string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    std::vector<std::string> requests = {"m", "statement"};
    const std::vector<std::map<int,int>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}




int main() {
    //Engine engine("config.json", "request.json" , "answer.json" );
    //engine.work();



}
