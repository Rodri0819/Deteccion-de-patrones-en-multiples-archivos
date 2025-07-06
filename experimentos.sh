#!/bin/bash

OUTPUT="resultados.csv"
EJECUTABLE="./main.exe"

DOCUMENTOS=(10 20 50 100)
PATRONES=(100 200 500 1000)
ALGORITMOS=("BM" "KMP" "RK" "SA")

REPETICIONES=20

# crear CSV si no existe
if [ ! -f "$OUTPUT" ]; then
  echo "Algoritmo,NumDocumentos,NumPatrones,TiempoConstruccion,TiempoBusqueda,MemoriaKB" > "$OUTPUT"
fi

for alg in "${ALGORITMOS[@]}"; do
  for docs in "${DOCUMENTOS[@]}"; do
    for pats in "${PATRONES[@]}"; do
      for ((i=1; i<=REPETICIONES; i++)); do
        echo "[$i/$REPETICIONES] Ejecutando: Alg=$alg, Docs=$docs, Pats=$pats"

        # guarda stdout y stderr en archivos separados
        out_tmp=$(mktemp)
        err_tmp=$(mktemp)

        # ejecuta y separa
        /usr/bin/time -v $EJECUTABLE "$docs" "$pats" "$alg" >"$out_tmp" 2>"$err_tmp"

        # lee los datos correctos
        tiempos=$(head -n1 "$out_tmp")
        memoria=$(grep "Maximum resident set size" "$err_tmp" | awk '{print $6}')

        # limpia
        rm -f "$out_tmp" "$err_tmp"


        # guarda al CSV
        echo "$alg,$docs,$pats,$tiempos,$memoria" >> "$OUTPUT"
      done
    done
  done
done

echo "✅ Experimentos completados. Resultados en: $OUTPUT"
