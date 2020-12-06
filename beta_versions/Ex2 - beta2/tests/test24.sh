#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m'
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 24 ~~~~\n${NC}"
./my_grep -E '\[(1|)[0-9]\](a|a)[0-q]\[...\]' tests/input_files/2013.html >tmp_output
grep  -E '\[(1|)[0-9]\](a|a)[0-q]\[...\]' tests/input_files/2013.html | diff tmp_output -


echo "${RED}~~~~ Test 24 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -E '\[(1|)[0-9]\](a|a)[0-q]\[...\]' tests/input_files/2013.html > tmp_output
grep -E '\[(1|)[0-9]\](a|a)[0-q]\[...\]' tests/input_files/2013.html | diff tmp_output -

