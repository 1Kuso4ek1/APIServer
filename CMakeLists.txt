cmake_minimum_required(VERSION 3.10)

project(APIServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(APIServer main.cpp src/APIBase.cpp src/Users.cpp src/Authorization.cpp)

include_directories(include)

target_include_directories(APIServer PUBLIC include "/usr/local/include/httpserver/include")
target_link_libraries(APIServer jsoncpp httpserver)
