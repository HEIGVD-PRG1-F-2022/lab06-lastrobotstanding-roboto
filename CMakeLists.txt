cmake_minimum_required(VERSION 3.23)
project(LastRobotStanding)

set(CMAKE_CXX_STANDARD 20)

add_executable(LastRobotStanding main.cpp robots/Roboto.cpp robots/Roboto.h robots/RandomRoboto.cpp robots/RandomRoboto.h robots/BetterR.cpp robots/BetterR.h Game.cpp Game.h helper.cpp helper.h)

include(FetchContent) # once in the project to include the module

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.2.5
        )
FetchContent_MakeAvailable(libdio)


include(FetchContent) # once in the project to include the module

FetchContent_Declare(librobots
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/librobots.git
        GIT_TAG v0.2.10
        )
FetchContent_MakeAvailable(librobots)

# Replace `PROJECT` with the name of your executable
target_link_libraries(LastRobotStanding PRIVATE libdio)
target_link_libraries(LastRobotStanding PRIVATE librobots)