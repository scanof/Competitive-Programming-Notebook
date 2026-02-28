#!/bin/bash
g++ -O2 -o a $1 && g++ -O2 -o b $2 && g++ -O2 -o g $3
for((i=1;;i++)); do
  ./g $i > in
  ./a < in > o1
  ./b < in > o2
  diff o1 o2 > /dev/null || { echo "Test $i:"; cat in; echo "---"; cat o1; echo "---"; cat o2; break; }
  echo -ne "\r$i"
done
