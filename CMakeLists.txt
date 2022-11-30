cmake_minimum_required(VERSION 3.23)
project(Refactor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Refactor main.cpp robots/Roboto.cpp robots/Roboto.h const.h Game.cpp Game.h RobotState.cpp RobotState.h)

include(FetchContent) # once in the project to include the module

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.1.10
        )
FetchContent_MakeAvailable(libdio)

# Here are your other declarations, like `add_executable`

# Replace `PROJECT` with the name of your executable
target_link_libraries(Refactor PRIVATE libdio)