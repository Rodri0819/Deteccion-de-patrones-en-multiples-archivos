#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <unordered_set>

using namespace std;

string generar_cadena_aleatoria(int longitud, const string& alfabeto, mt19937& generador) {
    uniform_int_distribution<> dist(0, alfabeto.size()-1);
    string resultado;
    for (int i = 0; i < longitud; ++i)
        resultado += alfabeto[dist(generador)];
    return resultado;
}

vector<string> generar_patrones_existentes(const string& texto, int cantidad, int longitud, mt19937& generador) {
    vector<string> patrones;
    uniform_int_distribution<> dist(0, texto.size() - longitud - 1);

    for (int i = 0; i < cantidad; ++i) {
        int inicio = dist(generador);
        patrones.push_back(texto.substr(inicio, longitud));
    }

    return patrones;
}

vector<string> generar_patrones_inexistentes(const string& texto, int cantidad, int longitud, mt19937& generador, const string& alfabeto) {
    vector<string> patrones;
    unordered_set<string> existentes;
    for (int i = 0; i <= texto.size() - longitud; ++i)
        existentes.insert(texto.substr(i, longitud));

    while (patrones.size() < cantidad) {
        string candidato = generar_cadena_aleatoria(longitud, alfabeto, generador);
        if (existentes.find(candidato) == existentes.end()) {
            patrones.push_back(candidato);
        }
    }

    return patrones;
}


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

// Aquí irían las funciones para generar patrones…

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Uso: " << argv[0] << " <texto.txt> <cantidad> <longitud> <modo>\n";
        cerr << "Modo: EXISTEN | NO_EXISTEN | MIXTO\n";
        return 1;
    }

    string archivo_texto = argv[1];
    int cantidad_patrones = stoi(argv[2]);
    int longitud_patron = stoi(argv[3]);
    string modo = argv[4];

    ifstream entrada(archivo_texto);
    if (!entrada.is_open()) {
        cerr << "No se pudo abrir el archivo de texto.\n";
        return 1;
    }

    string texto((istreambuf_iterator<char>(entrada)), istreambuf_iterator<char>());
    entrada.close();

    mt19937 generador(random_device{}());

    //OJO: ACÁ GENERAMOS LOS PATRONES CON ACGT COMO LETRAS UNICAS DE LOS PATRONESS
    string alfabeto = "ACGT";
    vector<string> patrones;

    if (modo == "EXISTEN") {
        patrones = generar_patrones_existentes(texto, cantidad_patrones, longitud_patron, generador);
    }
    else if (modo == "NO_EXISTEN") {
        patrones = generar_patrones_inexistentes(texto, cantidad_patrones, longitud_patron, generador, alfabeto);
    }
    else if (modo == "MIXTO") {
        int mitad = cantidad_patrones / 2;
        auto existentes = generar_patrones_existentes(texto, mitad, longitud_patron, generador);
        auto inexistentes = generar_patrones_inexistentes(texto, cantidad_patrones - mitad, longitud_patron, generador, alfabeto);
        patrones.insert(patrones.end(), existentes.begin(), existentes.end());
        patrones.insert(patrones.end(), inexistentes.begin(), inexistentes.end());
    }
    else {
        cerr << "Modo inválido. Usa EXISTEN, NO_EXISTEN o MIXTO\n";
        return 1;
    }

    string nombre_salida;
    if (modo == "EXISTEN")
        nombre_salida = "../patrones/Patrones_Existentes";
    else if (modo == "NO_EXISTEN")
        nombre_salida = "../patrones/Patrones_NoExistentes";
    else
        nombre_salida = "../patrones/Patrones_Mixtos";

    ofstream salida(nombre_salida);
    if (!salida.is_open()) {
        cerr << "No se pudo abrir para escribir: " << nombre_salida << "\n";
        return 1;
    }

    for (const auto& patron : patrones)
        salida << patron << "\n";

    cout << "Generados " << patrones.size() << " patrones en " << nombre_salida << "\n";
    return 0;
}
