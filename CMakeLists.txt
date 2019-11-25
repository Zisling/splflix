cmake_minimum_required(VERSION 3.15)
project(splflix)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG )
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

#add_executable(test test.cpp
#        include/json.hpp
#        JsonReader.cpp
#        JsonReader.h
#        include/Watchable.h
#        src/Watchable.cpp
#        include/Session.h
#        src/Session.cpp
#        include/Action.h
#        src/Action.cpp
#        include/User.h
#        src/User.cpp
#        )
