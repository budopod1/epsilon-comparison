#!/usr/bin/env bash
set -e
cd "${0%/*}"

clang C/main.c -o C/main
./C/main
