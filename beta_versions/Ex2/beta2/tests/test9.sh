#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 9 - find    -v -i -E 'o\.pdf'  in 2013.html~~~~\n${NC}"
./my_grep  -v -i -E 'o\.pdf' tests/input_files/2013.html >tmp_output
grep  -v -i -E 'o\.pdf' tests/input_files/2013.html | diff tmp_output -


echo "${RED}~~~~ Test 9 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -v -i -E 'o\.pdf' tests/input_files/2013.html > tmp_output
grep -v -i -E 'o\.pdf' tests/input_files/2013.html | diff tmp_output -

