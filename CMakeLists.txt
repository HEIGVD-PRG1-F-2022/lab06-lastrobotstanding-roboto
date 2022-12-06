cmake_minimum_required(VERSION 3.23)
project(Refactor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Refactor main.cpp robots/Roboto.cpp robots/Roboto.h const.h Game.cpp Game.h)

include(FetchContent) # once in the project to include the module

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.2.1
        )
FetchContent_MakeAvailable(libdio)


include(FetchContent) # once in the project to include the module

FetchContent_Declare(librobots
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/librobots.git
        GIT_TAG v0.2.1
        )
FetchContent_MakeAvailable(librobots)

# Replace `PROJECT` with the name of your executable
target_link_libraries(Refactor PRIVATE libdio)
target_link_libraries(Refactor PRIVATE librobots)