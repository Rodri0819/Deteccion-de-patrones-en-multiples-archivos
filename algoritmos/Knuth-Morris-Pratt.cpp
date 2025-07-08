#include <iostream>
#include <vector>
#include <string>

using namespace std;

// PREFIX TABLE: Saber cuantas veces se repite un prefijo, que también es subfijo, por caracter
vector<int> LPS(const string& pattern){
    int size = pattern.size();
    vector<int> aux(size);

    // Asignamos cero a todo
    for (int i = 0; i < size; i++) {
	aux[i] = 0;
    }

    // Creamos dos selectores, i para seleccionar caracteres del patron y j para calcular prefijo-sufijo más largo
    // auxiliar
    int j = 0;
    int i = 1;

    // Bucle que espera que i llegue a la cantidad total de caracteres del patrón para terminar
    while(i < size){

	// Si el caracter del patrón selecionado es igual al patron con selección j entonces 
	// se mueven en uno los selectores y se asigna prefijo-sufijo más largo de esa iteración
	if(pattern[i] == pattern[j]){
	    j++;
	    aux[i] = j;
	    i++;
	}
	// Si el caracter del patrón selecionado no es igual al patron con selección j y j no está en el primer caracter, entonces j 
	// retrocede a la anterior prefijo-sufijo más largo 
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

    // Bucle que espera que i llegue a la cantidad total de caracteres del texto 
    while (i < txt_size){
	// Si los caracteres del patrón y texto son iguales mover selector
	if(pattern[j] == txt[i]){
	    i++;
	    j++;
	}
	// Si j iguala al patrón, queriendo decir que se encontró una referencia, se guarda la posicion y se retrocede j a su anterior
	// cantidad de caracteres del prefijo-sufijo más larga 
	if(j == patt_size){
	    posiciones.push_back(i-j);
	    j = lps[j-1];
	}
	else{
	    // Si el caracter del patron es distinta a la del texto seleccionado, entonces retroceder hasta solo la posición cantidad de caracteres del            prefijo-sufijo más larga anterior 
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

