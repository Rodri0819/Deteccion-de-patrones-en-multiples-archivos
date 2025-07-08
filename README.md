# Buscador de Patrones en Documentos

Este programa permite buscar patrones de texto dentro de múltiples documentos utilizando distintos algoritmos.

## Compilación
g++ -std=c++17 -o main.exe main.cpp algoritmos/Boyer-Moore.cpp algoritmos/Rabin-Karp.cpp algoritmos/Knuth-Morris-Pratt.cpp estructuras/suffix_array.cpp utils/CargarDocumentos.cpp

## Ejecución
./main.exe <num_documentos> <num_patrones> <algoritmo>

Para <algoritmo> las opciones son:

BM → Boyer-Moore

SA → Suffix Array

KMP → Knuth-Morris-Pratt

RK → Rabin-Karp
