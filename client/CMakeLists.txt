cmake_minimum_required(VERSION 3.27)
project(riddle_client)

set(CMAKE_CXX_STANDARD 11)

add_executable(riddle_client main.cpp
        include/ClientNetworkHandler.h
        include/UserInterface.h
        include/MainClient.h
        include/Parser.h
        src/ClientNetworkHandler.cpp
        src/Parser.cpp
        src/MainClient.cpp)
