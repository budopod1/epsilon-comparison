#!/usr/bin/env bash
set -e
cd "${0%/*}"

rm -rf Epsilon/Compiler
git clone https://github.com/budopod1/EpsilonLang.git ./Epsilon/Compiler
./Epsilon/Compiler/setup.bash
