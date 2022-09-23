#include "nlohmann/json.hpp"
#include "../WordCounter.h"
#include <iostream>
namespace answ {

    struct Answer{
        int docID;
        float rank;
        Answer() = default;
        Answer(const answ::Answer &answer)
        {
            this->docID = answer.docID;
            this->rank = answer.rank;
        }
        Answer(int docID, float rank)
        {
            this->docID = docID;
            this->rank = rank;
        }

        bool operator > (const answ::Answer answer) const
        {
            return this->rank > answer.rank ? true : false;
        }
        bool operator < ( const answ::Answer answer) const
        {
            return this->rank < answer.rank ? true : false;
        }


    };

    struct AnswerModel {
        bool result;
        std::vector<answ::Answer> answers;

        AnswerModel()
        {
            result = false;
        }
        nlohmann::json toDict() {
            nlohmann::json total;
            total["result"] = result;
            if(result)
            {
                std::vector<nlohmann::json> arr;
                if(answers.size() == 1)
                {
                    total["docid"] = answers[0].docID;
                    total["rank"] = answers[0].rank;
                }
                else {
                    for (auto i: answers) {
                        nlohmann::json buff;
                        buff["docid"] = i.docID;
                        buff["rank"] = i.rank;
                        arr.push_back(buff);
                    }
                    total["relevance"] = arr;
                }

            }
            return total;

        }

        void addAnswer(answ::Answer &answ) {
            try {
                answers.push_back(answ);
                result = true;
            }
            catch (...) {
                std::cerr << "answer cause exception" << std::endl;
            }

        }
    };


}


