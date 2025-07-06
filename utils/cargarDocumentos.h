#ifndef CARGARDOCUMENTOS_H
#define CARGARDOCUMENTOS_H

#include <string>
#include <vector>

std::string cargarDocumentos(const std::string& carpeta, std::vector<size_t>& offsets, size_t limite = SIZE_MAX);

#endif // CARGAR_DOCUMENTOS_H
