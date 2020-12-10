#! /usr/bin/env bash

RED='\033[0;31m'
NC='\033[0m' # No Color
Gre='\e[0;32m'
echo "${Gre}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${NC}"

echo "${RED}~~~~ Test 27 ~~~~\n${NC}"
./my_grep -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html >tmp_output
grep  -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html | diff tmp_output -

echo "${RED}~~~~ Test 27 - valgrind~~~~\n${NC}"
valgrind  --quiet --leak-check=yes ./my_grep -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html > tmp_output
grep -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -i -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html > tmp_output                                             
grep -i -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -i -b -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html > tmp_output
grep -i -b -E '(C|).(pDf|pdF).[i-y].' tests/input_files/2013.html | diff tmp_output -                                                                                                                                                                                          
valgrind  --quiet --leak-check=yes ./my_grep -i -b -E '}\/' tests/input_files/2013.html > tmp_output
grep -i -b -E '}\/' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -i -b -E ' ' tests/input_files/2013.html > tmp_output                                                                    
grep -i -b -E ' ' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -i -b -x -E 'pdf' tests/input_files/2013.html > tmp_output
grep -i -b -x -E 'pdf' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -i -n -E 'pdf' tests/input_files/2013.html > tmp_output                                                                
grep -i -n -E 'pdf' tests/input_files/2013.html | diff tmp_output -                                                                                                    

valgrind  --quiet --leak-check=yes ./my_grep -i -n -E '!' tests/input_files/2013.html > tmp_output                                                                    
grep -i -n -E '!' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -c 'a' tests/input_files/2013.html > tmp_output
grep -c 'a' tests/input_files/2013.html | diff tmp_output -                                                                                                          

valgrind --quiet --leak-check=yes ./my_grep -A 2 -c 'a' tests/input_files/2013.html > tmp_output
grep -A 2 -c 'a' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -v -c 'a' tests/input_files/2013.html > tmp_output
grep -v -c 'a' tests/input_files/2013.html | diff tmp_output -                                                                             









