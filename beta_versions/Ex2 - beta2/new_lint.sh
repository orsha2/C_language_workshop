#! /usr/bin/env bash

diff ~nimrodav/lint/.clang-format ./.clang-format
diff ~nimrodav/lint/.clang-tidy ./.clang-tidy

for f in *.c ; do
  ~nimrodav/lint/clang-format $f | diff $f -
done

if ls *.h 1> /dev/null 2>&1; then
  for f in *.h ; do
    ~nimrodav/lint/clang-format $f | diff $f -
  done
fi

~nimrodav/lint/clang-tidy -quiet *.c -- |& grep -v "warning generated" | grep -v "warnings generated" | grep -v "Suppressed"
