cmake_minimum_required(VERSION 3.29)
project(Deteccion_de_patrones_en_multiples_archivos)

set(CMAKE_CXX_STANDARD 14)

add_executable(Deteccion_de_patrones_en_multiples_archivos
        algoritmos/Boyer-Moore.cpp
        estructuras/suffix_array.cpp)
