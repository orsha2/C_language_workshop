#! /usr/bin/env bash                                                                                                                                                                                                                                                                                                                            ED='\033[0;31m'                                                                                                                                                         NC='\033[0m' # No Color
Gre='\e[0;32m';
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"
echo "${RED}~~~~ PRE TEST  ~~~\n${NC}"

echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"
echo "${RED}~~~~ CLANG FORMAT ~~~\n${NC}"
clang-format -style=file -i *.c *.h 

echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"
echo "${RED}~~~~ GCC *.C ~~~\n${NC}"
gcc -Wall -Wextra *.c -o my_grep



