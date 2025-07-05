#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<char, int> TablaDeOcurrencia(const string& patron) {
    unordered_map<char, int> tabla;
    int m = patron.size();
    //Recorremos el patron de derecha a izquierda
    for (int i = m - 1, pos = 0; i >= 0; --i, ++pos) {
        //Si el caracter no ha sido registrado todavia
        if (tabla.find(patron[i]) == tabla.end()) {
            //Lo registramos con la posicion desde la derecha
            tabla[patron[i]] = pos;
        }
    }

    return tabla;
}


vector<int> Sufijos(const string& patron) {
    int m = patron.size();
    vector<int> suff(m);
    suff[m - 1] = m;
    int g = m - 1;
    int f = m - 1;

    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g) {
            suff[i] = suff[i + m - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && patron[g] == patron[g + m - 1 - f]) {
                --g;
            }   
            suff[i] = f - g;
        }
    }

    return suff;
}

vector<int> TablaDeCoincidencia(const string& patron) {
    int m = patron.size();
    vector<int> good_suffix(m, m);
    vector<int> suff = Sufijos(patron);

    //Caso 1: sufijos que son prefijos
    for (int i = m - 1; i >= 0; --i) {
        if (suff[i] == i + 1) {
            for (int j = 0; j < m - 1 - i; ++j) {
                if (good_suffix[j] == m) {
                    good_suffix[j] = m - 1 - i;
                }
            }
        }
    }

    //Caso 2: sufijos internos
    for (int i = 0; i <= m - 2; ++i) {
        good_suffix[m - 1 - suff[i]] = std::min(good_suffix[m - 1 - suff[i]], m - 1 - i);
    }

    return good_suffix;
}

std::vector<int> BoyerMooreSearch(const std::string& texto, const std::string& patron) {
    std::vector<int> ocurrencias;

    int n = texto.size();
    int m = patron.size();

    if (m == 0 || n < m) return ocurrencias;

    //construir tablas auxiliares
    std::unordered_map<char, int> malCaracter = TablaDeOcurrencia(patron);
    std::vector<int> buenSufijo = TablaDeCoincidencia(patron);

    int desplazamiento = 0;

    while (desplazamiento <= n - m) {
        int j = m - 1;

        //comparar desde el final del patrón
        while (j >= 0 && patron[j] == texto[desplazamiento + j]) {
            j--;
        }

        if (j < 0) {
            //coincidencia completa
            ocurrencias.push_back(desplazamiento);

            //tras encontrar coincidencia, avanzar según buen sufijo
            int salto;
            if (buenSufijo[0] > 0) {
                salto = buenSufijo[0];
            } else {
                salto = 1;
            }
            desplazamiento += salto;

        } else {

            //fallo en j
            int salto_bs = buenSufijo[j];
            int salto_mc;

            char c = texto[desplazamiento + j];
            //Busca el valor que falló en la tabla de malcaracter
            auto it = malCaracter.find(c);

            //Si c no está en el patron
            if (it != malCaracter.end()) {
                // carácter sí está en el patrón, calcula cuanto mover el patron para alinaer c con su ultima aparicion, restando j(posición fallida) - posición en la ultima aparición de c en el patrón
                salto_mc = std::max(1, j - it->second);
            } else {
                // carácter no está en el patrón → saltar patrón completo
                salto_mc = m;
            }

            int salto;
            if (salto_bs > 0 && salto_bs < m) {
                salto = salto_bs;
            } else {
                salto = salto_mc;
            }

            desplazamiento += salto;
        }
    }

    return ocurrencias;
}
