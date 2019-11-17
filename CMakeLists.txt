cmake_minimum_required(VERSION 3.15)
project(splflix)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(splflix
        include/Action.h
        config1.json
        config2.json
        include/json.hpp
        src/Main.cpp
        include/Session.h
        include/User.h
        include/Watchable.h src/Action.cpp src/Session.cpp src/User.cpp src/Watchable.cpp)
