cmake_minimum_required(VERSION 3.8)
project(progetto_informatica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/arma.cpp
        includes/arma.hpp
        includes/item.cpp
        includes/item.hpp
        includes/personaggio.cpp
        includes/personaggio.hpp
        main.cpp
        mappa.cpp
        mappa.hpp
        stanza.cpp
        stanza.hpp)

add_executable(progetto_informatica ${SOURCE_FILES})