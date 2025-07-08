#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

// Construcción del Suffix Array (Prefix Doubling)
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n), temp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1;; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);

        temp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            temp[sa[i]] = temp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        
        rank = temp;
        if (rank[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

// Búsqueda binaria de un patrón en el texto usando el Suffix Array
vector<int> buscarPatronSA(const string &text, const string &pattern, const vector<int> &sa) {
    int n = text.size(), m = pattern.size();
    int left = 0, right = n - 1;
    vector<int> positions;

    // Buscar el rango [l, r) donde el patrón aparece
    // Primera aparición (lower bound)
    int l = -1, r = -1;

    // Buscar el inicio del rango
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        string suffix = text.substr(sa[mid], min(m, n - sa[mid]));
        if (suffix < pattern)
            lo = mid + 1;
        else
            hi = mid;
    }
    l = lo;

    // Buscar el final del rango
    lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        string suffix = text.substr(sa[mid], min(m, n - sa[mid]));
        if (suffix <= pattern)
            lo = mid + 1;
        else
            hi = mid;
    }
    r = lo;

    // Agregar todas las posiciones donde ocurre el patrón
    for (int i = l; i < r; i++) {
        positions.push_back(sa[i]);
    }

    return positions;
}

//Medir tiempo de construcción
pair<vector<int>, double> construirSuffixArrayConTiempo(const string& texto) {
    auto inicio = chrono::high_resolution_clock::now();
    auto sa = buildSuffixArray(texto);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;
    return {sa, duracion.count()};
}
