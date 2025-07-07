#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int TOTAL_CARACTERES = 256;

void calcularMalCaracter(const string& patron, vector<int>& malCaracter) {
    // Redimensiona el vectro malcaracter a 256 posiciones y rellena todas con -1
    malCaracter.assign(TOTAL_CARACTERES, -1);
    // Recorre cada posición del patrón
    for (int i = 0; i < patron.size(); i++) {
        //Guarda la posición i como la ultima aparición
        malCaracter[(unsigned char)patron[i]] = i;
    }
}

vector<int> BoyerMooreSearch(const string& texto, const string& patron) {
    int longitudTexto = texto.size();       // Longitud del texto
    int longitudPatron = patron.size();    // Longitud del patrón
    vector<int> posiciones;                // Guarda las posiciones donde se encuentra el patrón
    vector<int> malCaracter;              // Tabla de mal carácter

    calcularMalCaracter(patron, malCaracter);  // Calcula la tabla de última aparición de cada carácter en el patrón

    int desplazamiento = 0;               // Cuánto hemos desplazado el patrón en el texto

    // Mientras aún quede espacio suficiente para que el patrón encaje
    while (desplazamiento <= longitudTexto - longitudPatron) {
        int indicePatron = longitudPatron - 1;   // Empezamos comparando por la última letra del patrón

        // Comparar caracteres del patrón con el texto de derecha a izquierda
        while (indicePatron >= 0 && patron[indicePatron] == texto[desplazamiento + indicePatron]) {
            indicePatron--; // Si coinciden, seguimos a la izquierda
        }

        if (indicePatron < 0) {   // Si terminamos la comparación y todo coincidió
            posiciones.push_back(desplazamiento);  // Guardamos la posición de la coincidencia

            // Si todavía queda texto para seguir buscando
            if (desplazamiento + longitudPatron < longitudTexto) {
                int siguienteCaracter = (unsigned char)texto[desplazamiento + longitudPatron];
                // Saltamos el patrón hasta alinear con la siguiente posible coincidencia
                desplazamiento += longitudPatron - malCaracter[siguienteCaracter];
            } else {
                desplazamiento += 1;  // Si ya no queda más texto, avanzamos solo 1
            }

        } else {
            // Si hubo una falla en la comparación
            int caracterActual = (unsigned char)texto[desplazamiento + indicePatron];
            int ultimaOcurrencia = malCaracter[caracterActual]; // última aparición del carácter que falló

            int salto = indicePatron - ultimaOcurrencia;  // Calculamos cuánto podemos saltar

            if (salto < 1) {
                salto = 1;  // Saltar al menos 1 si no hay mejor opción
            }

            desplazamiento += salto;  // Avanzamos el patrón según el salto calculado
        }
    }

    return posiciones;  // Devolvemos todas las posiciones donde encontramos el patrón
}
