cmake_minimum_required(VERSION 3.10)
project(CPP_Drone_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find libraries on my system
#find_package(raylib REQUIRED)
#find_packages(glm REQUIRED)

#Executable target what we tell to compile
add_executable(CPP_Drone_Simulator
    src/main.cpp
    src/Entity.cpp
    src/MovingEntity.cpp
    src/Drone.cpp
    src/Rotor.cpp
)

find_library(RAYLIB_LIBRARY NAMES raylib REQUIRED)
find_library(GLM_LIBRARY NAMES glm REQUIRED)

target_include_directories(CPP_Drone_Simulator PRIVATE include)
target_link_libraries(CPP_Drone_Simulator PRIVATE 
    ${RAYLIB_LIBRARY}
    GL
    m
    pthread
    dl
    rt
    dl
    X11
    
    ${GLM_LIBRARY}) #this replaces -lraylib -lglm
