#!/usr/bin/env bash
set -e
cd "${0%/*}"

echo "Compiling C..."
clang -O3 C/main.c -o C/main
echo "Compiled C"
echo

echo "Compiling C#..."
mcs Csharp/Main.cs
echo "Compiled C#"
echo

echo "Compiling Epsilon..."
mono Epsilon/Compiler/Epsilon.exe compile Epsilon/entry.epsl
echo "Compiled Epsilon"
echo

echo "Not compiling Python"
echo

echo "Compiling Rust..."
rustc -C opt-level=3 Rust/main.rs -o Rust/main
echo "Compiled Rust"
echo
