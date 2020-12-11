#! /usr/bin/env bash

for f in *.c ; do
  clang-format $f | diff $f -
done

if ls *.h 1> /dev/null 2>&1; then
  for f in *.h ; do
    clang-format $f | diff $f -
  done
fi

clang-tidy *.c --  
