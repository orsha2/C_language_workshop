#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 10 - find    -x bla'  in 2013.html~~~~\n${NC}"
./my_grep  -x bla tests/input_files/in10 >tmp_output
grep  -x bla tests/input_files/in10 | diff tmp_output -


echo "${RED}~~~~ Test 10 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -x bla tests/input_files/in10 > tmp_output
grep -x bla tests/input_files/in10 | diff tmp_output -

