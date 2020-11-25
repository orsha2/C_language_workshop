
my_grep: main.o cmd_parser.o error_mgr.o my_grep.o init_regex.o
	gcc main.o cmd_parser.o error_mgr.o my_grep.o init_regex.o -o my_grep

main.o: main.c cmd_parser.h error_mgr.h init_regex.h my_grep.h 

cmd_parser.o: cmd_parser.c error_mgr.h init_regex.h

error_mgr.o: error_mgr.c 

init_regex.o: init_regex.c init_regex.h error_mgr.h

.PHONY: all clean test
clean:
	-rm *.o my_grep

all: 
	make
			
test:
	sh run_all.sh
