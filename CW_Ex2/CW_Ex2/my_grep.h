#ifndef MY_GREP_H
#define MY_GREP_H

#include "init_regex.h"
#include <stdio.h>

void print_expression_and_flags(Regex_And_Flags *my_regex_and_flags, char *expression);
void print_regex(Regex_And_Flags *my_regex_and_flags);
void grep_execute_on_stream(FILE *input_stream, Regex_And_Flags *my_regex_and_flags);

#endif
