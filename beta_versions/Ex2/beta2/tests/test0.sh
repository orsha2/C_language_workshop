#! /usr/bin/env bash


RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"
echo "${RED}~~~~ Test 0 - empty file ~~~~\n${NC}"
./my_grep a tests/input_files/empty_file >tmp_output
grep a tests/input_files/empty_file | diff -b  tmp_output -

echo "${RED}~~~~ Test 0 with valgrind ~~~~\n${NC}" 
valgrind  --quiet --leak-check=yes ./my_grep a tests/input_files/empty_file >tmp_output
grep a tests/input_files/empty_file | diff -b tmp_output -

