cmake_minimum_required(VERSION 3.10)

project(APIServer)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLiteCpp REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Threads REQUIRED)

add_executable(APIServer main.cpp src/APIBase.cpp src/Users.cpp src/Authorization.cpp src/FileResponse.cpp)

include_directories(include)

target_include_directories(APIServer PUBLIC include "/usr/local/include/httpserver/include")
target_link_libraries(APIServer jsoncpp httpserver SQLiteCpp jsoncpp_lib stdc++fs Threads::Threads)
