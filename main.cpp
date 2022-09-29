#include "DataModels/Engine.h"


int main() {
    Engine engine("config.json", "request.json" , "answer.json" );
    engine.work();

    return 0;
}
