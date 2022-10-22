#include "Engine.h"


int main() {
    Engine engine("config.json", "requests.json" , "answer.json" );
    engine.work();

    return 0;
}
