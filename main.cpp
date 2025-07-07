#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <numeric>
#include "algoritmos/Boyer-Moore.h"
#include "algoritmos/Knuth-Morris-Pratt.h"
#include "algoritmos/Rabin-Karp.h"
#include "estructuras/suffix_array.h"
#include "utils/cargarDocumentos.h"
namespace fs = std::filesystem;
using namespace std;

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
        cerr << "Algoritmos soportados: BM, SA, KMP, RK\n";
        return 1;
    }

    int num_docs = stoi(argv[1]);
    int num_pats = stoi(argv[2]);
    string algoritmo = argv[3];

    if (algoritmo != "BM" && algoritmo != "SA" && algoritmo != "KMP" && algoritmo != "RK") {
        cerr << "Algoritmo invalido: " << algoritmo << endl;
        cerr << "Opciones validas: BM, SA, KMP, RK\n";
        return 1;
    }

    ////////////////////////DATOS
    string carpeta = "datasets/DNA";
    string archivoPatrones = "patrones/Patrones_NoExistentes";

    vector<size_t> offsets;
    string texto = cargarDocumentos(carpeta, offsets, num_docs);
    vector<string> patrones = cargarPatrones(archivoPatrones, num_pats);

    int patrones_encontrados = 0;  // total de ocurrencias de todos los patrones

    double tiempo_construccion = 0.0;
    double tiempo_busqueda = 0.0;

    if (algoritmo == "SA") {
        vector<int> sa;

        auto resultado = construirSuffixArrayConTiempo(texto);
        sa = resultado.first;
        tiempo_construccion = resultado.second;

        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto ocurrencias = buscarPatronSA(texto, sa, patron);
                patrones_encontrados += ocurrencias.size();
            }
        });

        cout << tiempo_construccion << "," << tiempo_busqueda << endl;
        cout << "Ocurrencias totales encontradas: " << patrones_encontrados << endl;
    }

    else if (algoritmo == "BM") {
        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto posicionesBM = BoyerMooreSearch(texto, patron);
                patrones_encontrados += posicionesBM.size();
            }
        });

        cout << tiempo_busqueda << endl;
        cout << "Ocurrencias totales encontradas: " << patrones_encontrados << endl;
    }

    else if (algoritmo == "KMP") {
        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto posicionesKMP = KMPAlg(patron, texto);
                patrones_encontrados += posicionesKMP.size();
            }
        });

        cout << tiempo_busqueda << endl;
        cout << "Ocurrencias totales encontradas: " << patrones_encontrados << endl;
    }

    else if (algoritmo == "RK") {
        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto posicionesRK = search(patron, texto);
                patrones_encontrados += posicionesRK.size();
            }
        });

        cout << tiempo_busqueda << endl;
        cout << "Ocurrencias totales encontradas: " << patrones_encontrados << endl;
    }

    if (algoritmo == "SA")
        cout << "Tiempo construccion estructura: " << tiempo_construccion << " segundos\n";

    return 0;
}
