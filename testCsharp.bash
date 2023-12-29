#!/usr/bin/env bash
set -e
cd "${0%/*}"

mcs Csharp/Main.cs
mono Csharp/Main.exe
