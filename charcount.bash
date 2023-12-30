#!/usr/bin/env bash
set -e
cd "${0%/*}"

echo "C uses $(./charcount.py C/main.c) characters"
echo "C# uses $(./charcount.py Csharp/Main.cs) characters"
echo "Epsilon uses $(./charcount.py Epsilon/main.epsl) characters"
echo "Python uses $(./charcount.py Python/main.py) characters"
echo "Rust uses $(./charcount.py Rust/main.rs) characters"
