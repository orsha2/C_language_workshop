#! /usr/bin/env bash

ED='\033[0;31m'
NC='\033[0m' # No Color

echo "${RED}~~~~ RUN ALL ~~~\n${NC}"
sh tests/test0.sh
sh tests/test1.sh
sh tests/test2.sh
sh tests/test3.sh
sh tests/test4.sh
sh tests/test5.sh
sh tests/test6.sh
sh tests/test7.sh
sh tests/test8.sh
sh tests/test9.sh
sh tests/test10.sh
rm -rf tmp_output
