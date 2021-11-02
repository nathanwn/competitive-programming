#!/bin/bash

for((i = 1; ; ++i)); do
    if [[ ! -f "$i.in" ]] ; then
        echo 'Done.'
        exit 0
    fi
    echo "# Test $i"
    ./main < "$i.in" > "$i.out"
    diff -w "$i.out" "$i.ans" || break
done
