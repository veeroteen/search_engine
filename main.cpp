#include <iostream>
#include <vector>
#include "DataModels/Engine.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <random>
#include "DataModels/Models/WordIndex.h"
#include <algorithm>
#include <cmath>



int main() {
    Engine engine("config.json", "request.json" , "answer.json" );
    engine.work();





    return 0;


}
