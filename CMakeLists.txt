cmake_minimum_required(VERSION 3.10)
project(Deteccion_de_patrones_en_multiples_archivos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Deteccion_de_patrones_en_multiples_archivos
        main.cpp
        algoritmos/Boyer-Moore.cpp
        estructuras/suffix_array.cpp
        algoritmos/Boyer-Moore.h
        utils/generarPatrones.cpp
        utils/cargarDocumentos.cpp
        algoritmos/Robin-Karp.h
        algoritmos/Knuth-Morris-Pratt.h
        algoritmos/Rabin-Karp.cpp
)
