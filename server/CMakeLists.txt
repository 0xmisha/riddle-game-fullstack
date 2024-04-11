cmake_minimum_required(VERSION 3.27)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(server main.cpp
        include/MainServer.h
        include/ClientHandler.h
        include/Riddle.h
        include/GameManager.h
        include/Parser.h
        include/ServerNetworkHandler.h
        src/ClientHandler.cpp
        src/GameManager.cpp
        src/MainServer.cpp
        src/Parser.cpp
        src/Riddle.cpp
)
