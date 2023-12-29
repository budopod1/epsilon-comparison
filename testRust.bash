#!/usr/bin/env bash
set -e
cd "${0%/*}"

rustc Rust/main.rs -o Rust/main
./Rust/main
