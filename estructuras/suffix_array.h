#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include "string"
#include "vector"
#include "utility"

std::vector<int> buildSuffixArray(const std::string& texto);
std::vector<int> buscarPatronSA(const std::string& texto, const std::vector<int>& sa, const std::string& patron);
std::pair<std::vector<int>, double> construirSuffixArrayConTiempo(const std::string & texto);
#endif