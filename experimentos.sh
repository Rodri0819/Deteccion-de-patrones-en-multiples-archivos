#!/bin/bash

OUTPUT="resultados.csv"
EJECUTABLE="./main.exe"

# puedes modificar aquí los rangos
DOCUMENTOS=(10 20 50 100)
PATRONES=(100 200 500 1000)
ALGORITMOS=("BM" "KMP" "RK")

REPETICIONES=20

# crear CSV si no existe
if [ ! -f "$OUTPUT" ]; then
  echo "Algoritmo,NumDocumentos,NumPatrones,Existe,TiempoConstruccion,TiempoBusqueda" > "$OUTPUT"
fi

for alg in "${ALGORITMOS[@]}"; do
  for docs in "${DOCUMENTOS[@]}"; do
    for pats in "${PATRONES[@]}"; do
      for existe in "SI" "NO"; do
        for ((i=1; i<=REPETICIONES; i++)); do
          echo "[$i/$REPETICIONES] Alg=$alg, Docs=$docs, Pats=$pats, Existe=$existe"

          # ejecuta el programa con parámetros y flag de existencia
          # asumo que tu ejecutable entiende un cuarto argumento "SI"/"NO"
          result=$($EJECUTABLE "$docs" "$pats" "$alg" "$existe")

          # anexa resultado al CSV
          echo "$alg,$docs,$pats,$existe,$result" >> "$OUTPUT"
        done
      done
    done
  done
done

echo "  ✅ Experimentos completados. Resultados en: $OUTPUT"
