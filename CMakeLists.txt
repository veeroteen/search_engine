cmake_minimum_required(VERSION 3.22)
project(search_engine)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp DataModels/WordCounter.h DataModels/Engine.cpp DataModels/Engine.h DataModels/JSONInterfaces/JSONBase.cpp DataModels/JSONInterfaces/JSONBase.h DataModels/JSONInterfaces/JSONConfig.cpp DataModels/JSONInterfaces/JSONConfig.h DataModels/JSONInterfaces/JSONRequest.cpp DataModels/JSONInterfaces/JSONRequest.h DataModels/JSONInterfaces/JSONAnswer.cpp DataModels/JSONInterfaces/JSONAnswer.h DataModels/JSONWorkers/Request.cpp DataModels/JSONWorkers/Request.h DataModels/JSONWorkers/Config.cpp DataModels/JSONWorkers/Config.h DataModels/Models/AnswerModel.h DataModels/JSONWorkers/Answer.cpp DataModels/JSONWorkers/Answer.h)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
