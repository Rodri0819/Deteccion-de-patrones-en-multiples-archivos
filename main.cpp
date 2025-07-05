#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string cargarDocumentos(const string& carpeta, vector<size_t>& offsets) {
    string texto;
    //Recorre todos los archivos de la carpeta
    for (const auto& entry : fs::directory_iterator(carpeta)) {
        //Lee el archivo actual para la lectura
        ifstream in(entry.path());
        //Si el archivo no se pudo abrir, se salta al siguiente
        if (!in.is_open())
            continue;
        //Guarda la posición actual de texto
        offsets.push_back(texto.size());

        string linea;
        //Bucle que lee el archivo linea por linea
        while (getline(in, linea))
            //Agrega la linea más un salto de linea al final
            texto += linea + "\n";

        //Una vez leido un archivo, añadimos el $
        texto += "$";
    }
    return texto;
}

//Función para medir el tiempo
template<typename Func>
double medirTiempo(Func f) {
    auto inicio = chrono::high_resolution_clock::now();
    f();
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;
    return duracion.count();
}

int main() {
    vector<size_t> offsets;
    string texto = cargarDocumentos("datasets/DNA", offsets);

    cout << "Texto concatenado con longitud: " << texto.size() << endl;
    cout << "Cantidad de documentos: " << offsets.size() << endl;

    for (size_t i = 0; i < offsets.size(); ++i) {
        cout << "Documento " << i+1 << " comienza en posicion " << offsets[i] << endl;
    }

    return 0;
}