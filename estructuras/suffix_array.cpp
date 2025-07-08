#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstring>

using namespace std;

struct Suffix {
    int index;
    const char* suff;
};

bool cmp(const Suffix& a, const Suffix& b) {
    return strcmp(a.suff, b.suff) < 0;
}

vector<int> buildSuffixArray(const string& texto) {
    int n = texto.size();
    vector<Suffix> suffixes(n);

    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suff = texto.c_str() + i;
    }

    sort(suffixes.begin(), suffixes.end(), cmp);

    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++) {
        suffixArr[i] = suffixes[i].index;
    }

    return suffixArr;
}

vector<int> buscarPatronSA(const string& texto, const vector<int>& sa, const string& patron) {
    vector<int> ocurrencias;
    int n = texto.size(), m = patron.size();
    int l = 0, r = n-1;

    while (l <= r) {
        int mid = (l + r) / 2;
        string sufijo = texto.substr(sa[mid], min(m, n-sa[mid]));
        int cmp = patron.compare(sufijo);

        if (cmp == 0) {
            int i = mid;
            while (i >= l && texto.compare(sa[i], m, patron) == 0) {
                ocurrencias.push_back(sa[i]);
                i--;
            }
            i = mid + 1;
            while (i <= r && texto.compare(sa[i], m, patron) == 0) {
                ocurrencias.push_back(sa[i]);
                i++;
            }
            break;
        } else if (cmp < 0) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return ocurrencias;
}

//Medir tiempo de construcción
pair<vector<int>, double> construirSuffixArrayConTiempo(const string& texto) {
    auto inicio = chrono::high_resolution_clock::now();
    auto sa = buildSuffixArray(texto);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;
    return {sa, duracion.count()};
}
