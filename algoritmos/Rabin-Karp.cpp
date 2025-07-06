#include <iostream>
#include <vector>
using namespace std;

vector<int> search(const string &pat, const string &txt){
    
    int ASCII = 256;
    int Colisiones = 101;             //Número primo para reducir colisiones en la tabla hash
    int Largo_patron = pat.length();
    int Largo_texto = txt.length();
    int Hash_patron = 0;              
    int Hash_texto = 0;
    int factor = 1;
    
    vector<int> posiciones;           //Vector para almacenar las posiciones de coincidencias
    
    // Calcular el valor del factor para el hash
    // La formula usada para el factor es: ASCII^(Largo_patron - 1) % Colisiones
    for (int i = 0; i < Largo_patron - 1; i++) 
        factor = (factor * ASCII) % Colisiones;
    
    // Calcular el hash del patrón y del texto para la primera iteración (primera ventana)
    for (int i = 0; i < Largo_patron; i++){
        Hash_patron = (ASCII * Hash_patron + pat[i]) % Colisiones; 
        Hash_texto = (ASCII * Hash_texto + txt[i]) % Colisiones;
    }
    // Utiliza una "ventana deslizante" para comparar el hash del patrón con el hash del texto
    for (int i = 0; i <= Largo_texto - Largo_patron; i++){
        
        // Si los hashes coinciden, verifica si los caracteres son iguales
        if (Hash_patron == Hash_texto){
            bool coincidencia = true;
            for (int j = 0; j < Largo_patron; j++){
                if (txt[i + j] != pat[j]){
                
                    coincidencia = false;
                    break;
                }
            }
            if (coincidencia)
                posiciones.push_back(i + 1);
        }
        // Calcula el hash para la siguiente iteración (ventana deslizante)
        if (i < Largo_texto - Largo_patron){
            
            Hash_texto = (ASCII * (Hash_texto - txt[i] * factor) + txt[i + Largo_patron]) % Colisiones;
            // Asegura que el hash sea positivo
            if (Hash_texto < 0)
                Hash_texto += Colisiones;
        }
    }
    // Retorna un vector de posiciones donde coincidia el patrón
    return posiciones;
}
