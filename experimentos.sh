#!/bin/bash

OUTPUT="resultados.csv"
EJECUTABLE="./main"

DOCUMENTOS=(10 20 50 100)
PATRONES=(100 200 500 1000)
ALGORITMOS=("BM" "SA")

REPETICIONES=20

echo "Algoritmo,NumDocumentos,NumPatrones,TiempoConstruccion,TiempoBusqueda" > "$OUTPUT"

for alg in "${ALGORITMOS[@]}"; do
  for docs in "${DOCUMENTOS[@]}"; do
    for pats in "${PATRONES[@]}"; do
      for ((i=1; i<=REPETICIONES; i++)); do
        echo "[$i/20] Ejecutando: Alg=$alg, Docs=$docs, Pats=$pats"
        result=$($EJECUTABLE "$docs" "$pats" "$alg")
        echo "$result" >> "$OUTPUT"
      done
    done
  done
done

echo "Experimentos completados. Resultados en: $OUTPUT"
