#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 12 - find  -E '(bla|li)' in 3 lines~~~~\n${NC}"
./my_grep -E '(bla|li)' tests/input_files/3lines >tmp_output
grep -E '(bla|li)' tests/input_files/3lines | diff tmp_output -


echo "${RED}~~~~ Test 12 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -E '(bla|li)' tests/input_files/3lines > tmp_output
grep -E '(bla|li)' tests/input_files/3lines | diff tmp_output -

