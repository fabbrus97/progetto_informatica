cmake_minimum_required(VERSION 3.8)
project(progetto_informatica)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

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
        stanza.hpp
        termcolor.hpp)

add_executable(progetto_informatica ${SOURCE_FILES})