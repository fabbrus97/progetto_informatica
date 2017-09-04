cmake_minimum_required(VERSION 3.8)
project(progetto_informatica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/arco.cpp
        includes/arco.h
        includes/arma.cpp
        includes/arma.h
        includes/coltello.cpp
        includes/coltello.h
        includes/item.cpp
        includes/item.h
        includes/mob1.cpp
        includes/mob1.h
        includes/mob2.cpp
        includes/mob2.h
        includes/mob3.cpp
        includes/mob3.h
        includes/personaggio.cpp
        includes/personaggio.h
        includes/pg.cpp
        includes/pg.h
        includes/spada.cpp
        includes/spada.h
        main.cpp
        mappa.cpp
        mappa.hpp
        stanza.cpp
        stanza.hpp)

add_executable(progetto_informatica ${SOURCE_FILES})