cmake_minimum_required(VERSION 3.25)
project(UnityDirectoryReader)

set(CMAKE_CXX_STANDARD 17)

add_executable(UnityDirectoryReader main.cpp
        headers/ObjectFromScene.h
        src/ObjectFromScene.cpp
        headers/DirectoryParser.h
        src/DirectoryParser.cpp
        headers/SceneParser.h
        src/SceneParser.cpp)

target_link_libraries(UnityDirectoryReader yaml-cpp)