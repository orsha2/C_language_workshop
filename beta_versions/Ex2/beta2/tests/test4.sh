#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 4 - find google -n in google.html~~~~\n${NC}"
./my_grep -n google tests/input_files/test_file_2 >tmp_output
grep google -n tests/input_files/test_file_2 | diff tmp_output -


echo "${RED}~~~~ Test 4 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -n google tests/input_files/test_file_2 >tmp_output
grep google -n tests/input_files/test_file_2 | diff tmp_output -
