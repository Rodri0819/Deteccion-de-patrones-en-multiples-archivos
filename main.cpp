#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "algoritmos/Boyer-Moore.h"

namespace fs = std::filesystem;
using namespace std;


string cargarDocumentos(const string& carpeta, vector<size_t>& offsets, size_t limite = SIZE_MAX) {
    string texto;
    size_t contador = 0;

    //Recorre todos los archivos de la carpeta y subcarpetas
    for (const auto& entry : fs::recursive_directory_iterator(carpeta)) {
        //Si no es un archivo normal, lo ignora
        if (!fs::is_regular_file(entry))
            continue;

        //Si se alcanzó el limite, se sale
        if (contador >= limite)
            break;

        //Abre el archivo actual para lectura
        ifstream in(entry.path());
        //Si no se pudo abrir, salta al siguiente
        if (!in.is_open())
            continue;

        //Guarda la posición actual del texto
        offsets.push_back(texto.size());

        string linea;
        //Lee el archivo línea por línea
        while (getline(in, linea))
            //Agrega la línea leída más un salto de línea
            texto += linea + "\n";

        texto += "$";
        //Aumenta el contador de documentos
        ++contador;
    }

    return texto;
}

vector<string> cargarPatrones(const string& archivo, size_t n) {
    vector<string> patrones;
    ifstream in(archivo);
    string linea;
    while (getline(in, linea) && patrones.size() < n) {
        patrones.push_back(linea);
    }
    return patrones;
}

//Función para medir el tiempo de ejecución de una función
template<typename Func>
double medirTiempo(Func f) {
    auto inicio = chrono::high_resolution_clock::now(); // Marca inicio
    f();                                                // Ejecuta la función
    auto fin = chrono::high_resolution_clock::now();    // Marca fin
    chrono::duration<double> duracion = fin - inicio;   // Calcula duración
    return duracion.count();                            // Devuelve en segundos
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <num_documentos> <num_patrones> <algoritmo>\n";
        return 1;
    }

    int num_docs = stoi(argv[1]);
    int num_pats = stoi(argv[2]);
    string algoritmo = argv[3];

    string carpeta = "datasets/DNA";
    string archivoPatrones = "patrones.txt"; // este archivo debe contener 1 patrón por línea

    vector<size_t> offsets;
    string texto = cargarDocumentos(carpeta, offsets, num_docs);
    vector<string> patrones = cargarPatrones(archivoPatrones, num_pats);

    double tiempo_total = medirTiempo([&]() {
        for (const auto& patron : patrones) {
            if (algoritmo == "BM") {
                BoyerMooreSearch(texto, patron);
            }

        }
    });

    // salida en formato CSV
    cout << algoritmo << "," << num_docs << "," << num_pats << "," << tiempo_total << endl;

    return 0;
}