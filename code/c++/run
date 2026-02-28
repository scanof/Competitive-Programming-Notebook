#!/bin/bash
G=$'\033[32m' R=$'\033[31m' N=$'\033[0m'
LE="$1" NU="$2"
g++ -O3 ${LE}.cpp -o ru || exit
for f in ${LE}/${LE}${NU}*.in; do
  ./ru < "$f" > tmp.res
  if diff -qwB tmp.res "${f%.in}.out" > /dev/null; then
    [[ "$3" != "-f" ]] && echo "$f:$G OK $N"
  else
    echo "$f:$R FAIL $N"
  fi
  cat tmp.res; echo
done