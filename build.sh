#!/bin/bash
g++ -o dfs.out dfs.cpp
./dfs.out < $1
make demo
for file in ./graph_texts/*
    do
        strip=${file##*/}
        strip="${strip%%.*}"
        echo $strip
        ./demo -K dot < $file > graph1.dot
        dot -Tsvg < graph1.dot > ./images/"$strip".svg
    done