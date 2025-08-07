#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 map.ber"
    exit 1
fi

while IFS= read -r line; do
    for ((i=0; i<${#line}; i++)); do
        c="${line:i:1}"
        case "$c" in
            1) printf "\033[90m%c\033[0m" "$c" ;;      # Gris
            0) printf "\033[32m%c\033[0m" "$c" ;;      # Vert
            P) printf "\033[97m%c\033[0m" "$c" ;;      # Blanc
            E) printf "\033[31m%c\033[0m" "$c" ;;      # Rouge
            C) printf "\033[33m%c\033[0m" "$c" ;;      # Jaune
            *) printf "%c" "$c" ;;                       # Autres sans couleur
        esac
    done
    printf "\n"
done < "$1"
