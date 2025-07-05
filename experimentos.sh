#!/bin/bash

OUTPUT="resultados.csv"
EJECUTABLE="./main"

DOCUMENTOS=(10 20 50 100)
PATRONES=(100 200 500 1000)
ALGORITMOS=("BM" "KMP" "RK")

REPETICIONES=20

# Cabecera del CSV
echo "Algoritmo,NumDocumentos,NumPatrones,Tiempo" > "$OUTPUT"

for alg in "${ALGORITMOS[@]}"; do
  for docs in "${DOCUMENTOS[@]}"; do
    for pats in "${PATRONES[@]}"; do
      for ((i=1; i<=REPETICIONES; i++)); do
        echo "Ejecutando: Alg=$alg, Docs=$docs, Pats=$pats, Rep=$i"
        $EJECUTABLE "$docs" "$pats" "$alg" >> "$OUTPUT"
      done
    done
  done
done

echo "✅ Experimentos completados. Resultados en: $OUTPUT"
