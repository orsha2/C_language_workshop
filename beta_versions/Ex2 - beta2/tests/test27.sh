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

valgrind  --quiet --leak-check=yes ./my_grep -A 2 -x a tests/input_files/2013.html > tmp_output
grep -A 2 -x a tests/input_files/2013.html | diff tmp_output -    

valgrind  --quiet --leak-check=yes ./my_grep -A 2 -b -x a tests/input_files/2013.html > tmp_output                        
grep -A 2 -b -x a tests/input_files/2013.html | diff tmp_output - 

valgrind  --quiet --leak-check=yes ./my_grep -A 2 -n -x a tests/input_files/2013.html > tmp_output                        
grep -A 2 -n -x a tests/input_files/2013.html | diff tmp_output -                                                                                                               
valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -x a tests/input_files/2013.html > tmp_output
grep -A 50 -n -x a tests/input_files/2013.html | diff tmp_output - 

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -v a tests/input_files/2013.html > tmp_output
grep -A 50 -n -v a tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -v -x a tests/input_files/2013.html > tmp_output
grep -A 50 -n -v -x a tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -v -b -x a tests/input_files/2013.html > tmp_output
grep -A 50 -n -v -b -x a tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -v -i -b -x A tests/input_files/2013.html > tmp_output
grep -A 50 -n -v -i -b -x A tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -c -v -i -b -x A tests/input_files/2013.html > tmp_output
grep -A 50 -n -c -v -i -b -x A tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -c -v -i -b -x -E 'A' tests/input_files/2013.html > tmp_output
grep -A 50 -n -c -v -i -b -x -E 'A' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -n -v -i -b -x -E 'A' tests/input_files/2013.html > tmp_output
grep -A 50 -n -v -i -b -x -E 'A' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -v -b -x -n -i -E '.....A' tests/input_files/2013.html > tmp_output
grep -A 50 -n -v -i -b -x -E '.....A' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 50 -v -b -n -i -E '.....A\{' tests/input_files/2013.html > tmp_output                                              
grep -A 50 -n -v -i -b -E '.....A\{' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -v -b -n -i -E '.....A\{' tests/input_files/2013.html > tmp_output                                               
grep -n -v -i -b -E '.....A\{' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -v -b -n -c -E '.....A\{' tests/input_files/2013.html > tmp_output
grep -v -b -n -c -E '.....A\{' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -n -b -x -E '.....A\{' tests/input_files/2013.html > tmp_output                                                     
grep -n -b -x -E '.....A\{' tests/input_files/2013.html | diff tmp_output -

valgrind  --quiet --leak-check=yes ./my_grep -A 33 -v -b -x -c -E '.....A\{' tests/input_files/2013.html > tmp_output                                                grep -A 33 -n -b -x -c -E '.....A\{' tests/input_files/2013.html | diff tmp_output - 

valgrind  --quiet --leak-check=yes ./my_grep -A 300 -v -b -x -c -E '.....A\{' tests/input_files/2013.html > tmp_output                                              grep -A 300 -n -b -x -c -E '.....A\{' tests/input_files/2013.html | diff tmp_output - 

valgrind  --quiet --leak-check=yes ./my_grep -A 3 -n -b -x -E 'ises\<\/h2\>' tests/input_files/2013.html > tmp_output                                          
grep -A 3 -n -b -x -E 'ises\<\/h2\>' tests/input_files/2013.html | diff tmp_output -

echo "part 2 "

valgrind  --quiet --leak-check=yes cat tests/input_files/2013.html | ./my_grep -i -E '.....[a-Z]' > tmp_output
cat tests/input_files/2013.html | grep -i -E '.....[a-Z]' | diff tmp_output -

valgrind  --quiet --leak-check=yes cat tests/input_files/2013.html | ./my_grep -i -E '.....[a-a]' > tmp_output                                                    
cat tests/input_files/2013.html | grep -i -E '.....[a-a]' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -E '.....[1-a]' > tmp_output
cat tests/input_files/2013.html | grep -E '.....[1-a]' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -i -E '.....[A-a]' > tmp_output
cat tests/input_files/2013.html | grep -i -E '.....[A-a]' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -i -E '.....[A-z]' > tmp_output
cat tests/input_files/2013.html | grep -i -E '.....[A-z]' | diff tmp_output - 

#cat tests/input_files/2013.html | ./my_grep -i -E '.....[1-a]' > tmp_output
#cat tests/input_files/2013.html | grep -i -E '.....[1-a]' | diff tmp_output - 

cat tests/input_files/2013.html | ./my_grep -i -E '.....[1-9][S-Z]' > tmp_output
cat tests/input_files/2013.html | grep -i -E '.....[1-9][S-Z]' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -i -n -b  -E '.....[1-9][a-y]' > tmp_output                                 
cat tests/input_files/2013.html | grep -i -n -b  -E '.....[1-9][a-y]' | diff tmp_output - 

cat tests/input_files/2013.html | ./my_grep -i -n -b  -E '.....[1-9][A-S]' > tmp_output
cat tests/input_files/2013.html | grep -i -n -b  -E '.....[1-9][A-S]' | diff tmp_output -


cat tests/input_files/2013.html | ./my_grep -i -n -c -b  -E '.....[1-9][A-S]' > tmp_output                                                                        
cat tests/input_files/2013.html | grep -i -n -b -c -E '.....[1-9][A-S]' | diff tmp_output -


cat tests/input_files/2013.html | ./my_grep -i -n -v -b  -E '.....[1-9][A-S](|).' > tmp_output
cat tests/input_files/2013.html | grep -i -n -b -v -E '.....[1-9][A-S](|).' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -i -A 22 -n -v -b  -E '.....[1-9][A-S](|).' > tmp_output                                                              
cat tests/input_files/2013.html | grep -i -A 22 -n -b -v -E '.....[1-9][A-S](|).' | diff tmp_output - 

cat tests/input_files/2013.html | ./my_grep -i -A 3 -x -n -v -b  -E '.....[1-9][A-S](|).' > tmp_output
cat tests/input_files/2013.html | grep -i -A 3 -x -n -b -v -E '.....[1-9][A-S](|).' | diff tmp_output -

cat tests/input_files/2013.html | ./my_grep -i -A 3 -x -n -b  -E '.....[1-9][A-S](|).' > tmp_output  
cat tests/input_files/2013.html | grep -i -A 3 -x -n -b -E '.....[1-9][A-S](|).' | diff tmp_output -


echo " part 3 "
