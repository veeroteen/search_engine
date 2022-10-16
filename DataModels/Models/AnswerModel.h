#include "nlohmann/json.hpp"
#include <iostream>
#pragma once

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

            if(this->rank > answer.rank)
            {
                return true;
            }
            if(this->rank == answer.rank && this->docID < answer.docID)
            {
                return true;
            }
            return false;
        }
        bool operator < ( const answ::Answer answer) const
        {
            if(this->rank < answer.rank)
            {
                return true;
            }
            if(this->rank == answer.rank && this->docID > answer.docID)
            {
                return true;
            }
            return false;
        }
        bool operator == (const answ::Answer answer) const
        {
            return (docID == answer.docID) && (rank == answer.rank) ? true : false;
        }

    };

    struct AnswerModel {
        int requestID;
        bool result;
        std::vector<answ::Answer> answers;

        AnswerModel()
        {
            result = false;
        }

        //convert answer to json format
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

        //add answer and set result true;
        void addAnswer(answ::Answer &answ) {
            answers.push_back(answ);
            result = true;
        }
    };


}


