#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 14 - find   -A 2 stdin   ~~~~\n${NC}"
cat tests/input_files/in14 | ./my_grep -A 2 my_grep > tmp_output
cat tests/input_files/in14 | grep -A 2 my_grep > diff tmp_output -


echo "${RED}~~~~ Test 14 - valgrind~~~~\n${NC}"
cat tests/input_files/in14 | valgrind  --quiet --leak-check=yes ./my_grep -A 2 my_grep > tmp_output
cat tests/input_files/in14 | grep -A 2 my_grep > diff tmp_output -

