#!/usr/bin/env bash
set -e
cd "${0%/*}"

echo "Benchmarking C#..."
time mono Csharp/Main.exe
echo

echo "Benchmarking Rust..."
time Rust/main
echo

echo "Benchmarking Epsilon..."
time Epsilon/main
echo

echo "Benchmarking C..."
time C/main
echo

echo "Benchmarking Python..."
time python -OO Python/main.py
echo
