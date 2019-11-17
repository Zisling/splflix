cmake_minimum_required(VERSION 3.15)
project(splflix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(splflix
        Action.h
        config1.json
        config2.json
        json.hpp
        Main.cpp
        Session.h
        User.h
        Watchable.h Action.cpp Session.cpp User.cpp Watchable.cpp)
