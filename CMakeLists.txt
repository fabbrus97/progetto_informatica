cmake_minimum_required(VERSION 3.8)
project(github)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/arma.cpp
        includes/arma.hpp
        includes/gameobjects.cpp
        includes/gameobjects.hpp
        includes/item.cpp
        includes/item.hpp
        includes/personaggio.cpp
        includes/personaggio.hpp
        CMakeLists.txt
        main.cpp
        mappa.cpp
        mappa.hpp
        stanza.cpp
        stanza.hpp)

add_executable(github ${SOURCE_FILES})