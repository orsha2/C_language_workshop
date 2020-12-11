
#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 17 - find  -E '\[(1|)[0-9]\\\]'   in in17 ~~~~\n${NC}"
./my_grep -E '\[(1|)[0-9]\]'  tests/input_files/in16 >tmp_output
grep -E '\[(1|)[0-9]\]'  tests/input_files/in16 | diff tmp_output -


echo "${RED}~~~~ Test 17 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -E '\[(1|)[0-9]\\\]'  tests/input_files/in17 > tmp_output
grep -E '\[(1|)[0-9]\\\]'  tests/input_files/in17 | diff tmp_output -

