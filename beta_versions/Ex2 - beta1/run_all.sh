#! /usr/bin/env bash

ED='\033[0;31m'
NC='\033[0m' # No Color

echo "${RED}~~~~ RUN ALL ~~~\n${NC}"
sh tests/pre_test.sh
sh tests/test0.sh
sh tests/test1.sh
sh tests/test2.sh
sh tests/test3.sh
rm -rf tmp_output
