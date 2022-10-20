#include "Engine.h"
#include "gtest/gtest.h"
#include "PreloadJSON.h"


using namespace std;

void TestPreload(const  std::string &cfg, const std::vector<std::string>& docs , const std::string req , const std::vector<std::string>& requests )
{
    setConfig( cfg, docs);
    setRequests(req,requests);
}
void TestRelativeIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<answ::Answer>>& expected
){
    std::string cfg = "testcfg.json";
    std::string req = "testreq.json";
    std::string answ = "testanws.json";
    TestPreload(cfg,docs,req,requests);
    Engine engine(cfg,req,answ);
    engine.work();
    std::ifstream file(answ);
    nlohmann::json dict;
    file >> dict;
    std::vector<std::vector<answ::Answer>> answer;
    for( auto i : dict["answers"]) {
        answer.emplace_back();
        if (i["result"]) {
            if(i["relevance"] != nullptr)
            {
                for(auto j : i["relevance"])
                {
                    answ::Answer buff(j["docid"] ,j["rank"]);
                    answer[answer.size()-1].push_back(buff);
                }
            }
            else
            {
                answ::Answer buff(i["docid"] ,i["rank"]);
                answer[answer.size()-1].push_back(buff);
            }
        }
    }
    ASSERT_EQ(answer, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const vector<string> request = {"moscow is the capital of russia"};
    const std::vector<vector<answ::Answer>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666666687},
                    {1, 0.666666687},
                    {2, 0.666666687}
            }
    };
    TestRelativeIndexFunctionality(docs,request,expected);
}


TEST(TestCaseRelativeIndex, TestSimple) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<std::vector<answ::Answer>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    TestRelativeIndexFunctionality(docs,request,expected);
}

void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        std::vector<std::string>& requests,
        const std::vector<std::map<int,int>>& expected
) {
    std::string cfg = "testcfg.json";
    std::string req = "testreq.json";
    TestPreload(cfg,docs,req,requests);
    std::vector<std::map<int,int>> result;
    WordIndex idx;
    Config config;
    config.loadConfig(cfg);
    idx.UpdateDocumentBase(config);

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
std::vector<std::string> requests = {"milk", "water", "cappuccino"};
const std::vector<std::map<int,int>> expected = {
        {
                {0, 4}, {1, 1}, {2, 5}
        }, {
                {0, 3}, {1, 2}, {2, 5}
        }, {
                {3, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
const std::vector<std::string> docs = {
        "A b c d e f g h i j k l",
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
