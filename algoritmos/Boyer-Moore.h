#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<char, int> TablaDeOcurrencia(const std::string& patron);

std::vector<int> Sufijos(const std::string& patron);

std::vector<int> TablaDeCoincidencia(const std::string& patron);

std::vector<int> BoyerMooreSearch(const std::string& texto, const std::string& patron);

#endif
