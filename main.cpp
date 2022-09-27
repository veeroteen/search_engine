#include <iostream>
#include <vector>
#include "DataModels/Engine.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <random>
struct Vector2i
{
    int x;
    int y;

    Vector2i(int x , int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator > (const Vector2i &vec) const
    {
        if((10 * this->y + this->x) > (10 * vec.y + vec.x))
        {
            return true;
        }
        return false;
    }
    bool operator < (const Vector2i &vec) const
    {
        if((10 * this->y + this->x) < (10 * vec.y + vec.x))
        {
            return true;
        }
        return false;
    }

};




int main() {
    Engine engine("config.json", "request.json" , "answer.json" );
    engine.work();
    /*
    std::map<Vector2i , std::string> dict;
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++) {
            dict[Vector2i(x,y)] = "ss";
        }
    }
    for( auto i : dict)
    {
        std::cout << i.first.x << " " << i.first.y  << "   " << i.second << std::endl;
    }
*/


}
