#include <iostream>
#include <vector>
using namespace std;

vector<int> search(const string &pat, const string &txt){
    
    int ASCII = 256;
    int Colisiones = 101;
    int Largo_patron = pat.length();
    int Largo_texto = txt.length();
    int Hash_patron = 0;
    int Hash_texto = 0;
    int factor = 1;
    
    vector<int> posiciones;
    
    for (int i = 0; i < Largo_patron - 1; i++)
        factor = (factor * ASCII) % Colisiones;

    for (int i = 0; i < Largo_patron; i++){
        
        Hash_patron = (ASCII * Hash_patron + pat[i]) % Colisiones;
        Hash_texto = (ASCII * Hash_texto + txt[i]) % Colisiones;
    }

    for (int i = 0; i <= Largo_texto - Largo_patron; i++){
        
        if (Hash_patron == Hash_texto){
            bool match = true;
            for (int j = 0; j < Largo_patron; j++){
                
                if (txt[i + j] != pat[j]){
                
                    match = false;
                    break;
                }
            }
            if (match)
                posiciones.push_back(i + 1);
        }

        if (i < Largo_texto - Largo_patron){
            
            Hash_texto = (ASCII * (Hash_texto - txt[i] * factor) + txt[i + Largo_patron]) % Colisiones;
            if (Hash_texto < 0)
                Hash_texto += Colisiones;
        }
    }
    return posiciones;
}
