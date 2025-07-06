
//Generar Patrones                 
.\generarpatrones.exe ../datasets/DNA/dna_00 2000 15 NO_EXISTEN

//Compilar main  
g++ -std=c++17 -o main.exe main.cpp algoritmos/Boyer-Moore.cpp estructuras/suffix_array.cpp utils/CargarDocumentos.cpp


