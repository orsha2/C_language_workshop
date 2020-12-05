
#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m';
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 15 - find  -E '(ab|a).(d|cd)[x-z]'  in in15 ~~~~\n${NC}"
./my_grep -E '(ab|a).(d|cd)[x-z]' tests/input_files/in15 >tmp_output
grep -E '(ab|a).(d|cd)[x-z]' tests/input_files/in15 | diff tmp_output -


echo "${RED}~~~~ Test 15 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -E '(ab|a).(d|cd)[x-z]' tests/input_files/in15 > tmp_output
grep -E '(ab|a).(d|cd)[x-z]' tests/input_files/in15 | diff tmp_output -

