cmake_minimum_required(VERSION 3.22)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850
)

set(JSON_BuildTests OFF CACHE INTERNAL "")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp DataModels/Models/WordCounter.h DataModels/Engine.cpp DataModels/Engine.h DataModels/JSONInterfaces/JSONBase.cpp DataModels/JSONInterfaces/JSONBase.h DataModels/JSONInterfaces/JSONConfig.cpp DataModels/JSONInterfaces/JSONConfig.h DataModels/JSONInterfaces/JSONRequest.cpp DataModels/JSONInterfaces/JSONRequest.h DataModels/JSONInterfaces/JSONAnswer.cpp DataModels/JSONInterfaces/JSONAnswer.h DataModels/JSONWorkers/Request.cpp DataModels/JSONWorkers/Request.h DataModels/JSONWorkers/Config.cpp DataModels/JSONWorkers/Config.h DataModels/Models/AnswerModel.h DataModels/JSONWorkers/Answer.cpp DataModels/JSONWorkers/Answer.h DataModels/Models/WordIndex.cpp DataModels/Models/WordIndex.h)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine)