#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<char, int> TablaDeOcurrencia(const string& patron) {
    unordered_map<char, int> tabla;
    int m = patron.size();

    for (int i = 0; i < m - 1; ++i) {
        tabla[patron[i]] = m - i - 1;
    }

    return tabla;
}
vector<int> Sufijos(const string& patron) {
    int m = patron.size();
    vector<int> suff(m);
    suff[m - 1] = m;
    int g = m - 1, f = 0;

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

    //wCaso 1: sufijos que son prefijos
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
        good_suffix[m - 1 - suff[i]] = m - 1 - i;
    }

    return good_suffix;
}
