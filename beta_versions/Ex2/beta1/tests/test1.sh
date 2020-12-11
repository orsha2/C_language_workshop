#! /usr/bin/env bash


RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 1 - find 'a' ~~~~\n${NC}"
./my_grep a tests/input_files/test_file_1 >tmp_output
grep a tests/input_files/test_file_1 | diff tmp_output -


echo "${RED}~~~~ Test 1  valgrind~~~~\n${NC}"
valgrind --leak-check=yes ./my_grep a tests/input_files/test_file_1 >tmp_output
grep a tests/input_files/test_file_1 | diff tmp_output -



