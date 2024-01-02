#!/usr/bin/env bash
set -e
cd "${0%/*}"

mono Epsilon/Compiler/Epsilon.exe compile Epsilon/main.epsl Epsilon/main
./Epsilon/main
