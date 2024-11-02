cmake_minimum_required(VERSION 3.10)

project(APIServer)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLiteCpp REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Threads REQUIRED)
find_package(restclient-cpp REQUIRED)
find_package(Catch2 3 REQUIRED)

# option(ENABLE_TEST OFF "Enable/disable test build with Catch2 main")

# if(ENABLE_TEST)
#     set(CATCH2_LIBRARY Catch2::Catch2WithMain)
# else()
#     set(CATCH2_LIBRARY Catch2::Catch2)
# endif()

add_executable(
    APIServer 

    main.cpp
    src/APIBase.cpp
    src/Users.cpp
    src/Authorization.cpp
    src/FileResponse.cpp
    src/WebServer.cpp
    src/Messaging.cpp)

add_executable(tests tests.cpp)

include_directories(include)

target_include_directories(APIServer PUBLIC include)
target_include_directories(tests PUBLIC "/usr/local/include/httpserver/include")

target_link_libraries(APIServer jsoncpp httpserver SQLiteCpp jsoncpp_lib stdc++fs Threads::Threads)
target_link_libraries(tests jsoncpp restclient-cpp Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(tests)
