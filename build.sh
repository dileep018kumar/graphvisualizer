#!/bin/bash
g++ -o dfs.out -I ./ dfs.cpp
./dfs.out < $1
make demo
for file in ./graph_texts/*
    do
        strip=${file##*/}
        strip="${strip%%.*}"
        echo $strip
        ./demo -Kdot < $file > graph1.dot
        dot -Tsvg < graph1.dot > ./images/"$strip".svg
        # inkscape -z -e ./png/"$strip".png -w 230 -h 1208 ./images/"$strip".svg
    done

# rm -r ./graph_texts/*