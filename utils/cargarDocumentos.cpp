#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


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
