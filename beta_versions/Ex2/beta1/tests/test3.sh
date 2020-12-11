#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 3 - stdin find bl in 3lines ~~~~\n${NC}"
cat tests/input_files/3lines | ./my_grep bl > tmp_output
cat tests/input_files/3lines | grep bl  | diff tmp_output -


echo "${RED}~~~~ Test 3 - valgrind~~~~\n${NC}"
valgrind --leak-check=yes cat tests/input_files/3lines | ./my_grep bl > tmp_output
cat tests/input_files/3lines | grep bl  | diff tmp_output -

