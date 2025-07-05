#include <iostream>
#include <vector>
#include <string>

using namespace std;

// PREFIX TABLE: Saber cuantas veces se repite un prefijo y subfijo por caracter
vector<int> LongestPrefixSufix(const string& pattern){
    int size = pattern.size();
    vector<int> aux(size);

    // Asignamos cero a todo
    for (int i = 0; i < size; i++) {
	aux[i] = 0;
    }

    int j = 0;
    int i = 1;

    while(i < size){
	if(pattern[i] == pattern[j]){
	    j++;
	    aux[i] = j;
	    i++;
	}
	else{
	    if(j != 0)
		j = aux[j-1];
	    else{
		aux[i] = 0;
		i++;
	    }
	}
    }

    return aux;
}

vector<int> KMPAlg(const string& pattern,const string& txt){
    int txt_size = txt.size();
    int patt_size = pattern.size();

    vector<int> lps = LongestPrefixSufix(pattern);
    int j = 0;
    int i = 0;

    // Para luego retornar un vector de posiciones donde coincidia el patrón
    vector<int> posiciones;

    while (i < txt_size){
	if(pattern[j] == txt[i]){
	    i++;
	    j++;
	}
	if(j == patt_size){
	    posiciones.push_back(i-j);
	    j = lps[j-1];
	}
	else{
	    if(i < txt_size && pattern[j] != txt[i]){
		if(j != 0)
		    j = lps[j-1];
		else
		    i++;
	    }
	}
    }

    return posiciones;
}

