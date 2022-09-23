#include <iostream>
#include <vector>
#include "DataModels/Engine.h"
#include "nlohmann/json.hpp"
#include <fstream>



int main() {
    Engine engine("config.json", "request.json" , "answer.json" );
    engine.work();

}
