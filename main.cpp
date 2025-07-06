#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <numeric>
#include "algoritmos/Boyer-Moore.h"
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
        cerr << "Algoritmos soportados: BM, SA\n";
        return 1;
    }

    int num_docs = stoi(argv[1]);
    int num_pats = stoi(argv[2]);
    string algoritmo = argv[3];

    if (algoritmo != "BM" && algoritmo != "SA") {
        cerr << "Algoritmo invalido: " << algoritmo << endl;
        cerr << "Opciones validas: BM, SA\n";
        return 1;
    }

    string carpeta = "datasets/DNA";
    string archivoPatrones = "patrones/Patrones_NoExistentes";

    vector<size_t> offsets;
    string texto = cargarDocumentos(carpeta, offsets, num_docs);
    vector<string> patrones = cargarPatrones(archivoPatrones, num_pats);

    int patrones_encontrados = 0;

    cout << "Cargando documentos y patrones...\n";
    cout << "Documentos cargados: " << num_docs << endl;
    cout << "Patrones cargados: " << num_pats << endl;
    cout << "Ejecutando busqueda con algoritmo: " << algoritmo << endl;

    double tiempo_construccion = 0.0;
    double tiempo_busqueda = 0.0;

    if (algoritmo == "SA") {
        vector<int> sa;

        tiempo_construccion = medirTiempo([&]() {
            auto resultado = construirSuffixArrayConTiempo(texto);
            sa = resultado.first;
            tiempo_construccion = resultado.second;
        });

        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto ocurrencias = buscarPatronSA(texto, sa, patron);
                if (!ocurrencias.empty()) {
                    cout << "Patron \"" << patron << "\" encontrado " << ocurrencias.size() << " veces.\n";
                    patrones_encontrados++;
                } else {
                    cout << "Patron \"" << patron << "\" no encontrado.\n";
                }
            }
        });
    }
    else if (algoritmo == "BM") {
        tiempo_busqueda = medirTiempo([&]() {
            for (const auto& patron : patrones) {
                auto posicionesBM = BoyerMooreSearch(texto, patron);
                if (!posicionesBM.empty()) {
                    cout << "Patron \"" << patron << "\" encontrado " << posicionesBM.size() << " veces.\n";
                    patrones_encontrados++;
                } else {
                    cout << "Patron \"" << patron << "\" no encontrado.\n";
                }
            }
        });
    }

    cout << "\nResumen final:\n";
    cout << "Algoritmo utilizado: " << algoritmo << endl;
    cout << "Documentos analizados: " << num_docs << endl;
    cout << "Patrones buscados: " << num_pats << endl;
    cout << "Patrones encontrados: " << patrones_encontrados << endl;

    if (algoritmo == "SA")
        cout << "Tiempo construccion estructura: " << tiempo_construccion << " segundos\n";

    cout << "Tiempo total busqueda: " << tiempo_busqueda << " segundos\n";

    return 0;
}
