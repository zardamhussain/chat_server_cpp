cmake_minimum_required(VERSION 3.15)
project(crow_server)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba
)                      
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_Declare(crow URL https://github.com/CrowCpp/Crow/releases/download/v1.0%2B1/crow-v1.0+1.tar.gz)
FetchContent_Declare(boost URL https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz)


FetchContent_MakeAvailable(cpr json crow boost)


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${crow_SOURCE_DIR}/include
    ${boost_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr nlohmann_json::nlohmann_json)