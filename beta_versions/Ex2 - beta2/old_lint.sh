#! /usr/bin/env bash

diff ~nimrodav/lint/.clang-format ./.clang-format
diff ~nimrodav/lint/.clang-tidy ./.clang-tidy

CLANG_TIDY=~nimrodav/clang+llvm-3.9.0-x86_64-linux-gnu-ubuntu-14.04/bin/clang-tidy

CLANG_FORMAT=~nimrodav/clang+llvm-3.9.0-x86_64-linux-gnu-ubuntu-14.04/bin/clang-format

for f in *.c *.h; do
  $CLANG_FORMAT $f | diff $f -
done

$CLANG_TIDY *.c *.h -- |& grep -v "warning generated" | grep -v "warnings generated" | grep -v "Suppressed"
