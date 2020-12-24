#ifndef HELPERS_H
#define HELPERS_H

#include "init_regex.h"

void print_expression_and_flags(Regex_And_Flags *my_regex_and_flags,
                                char *expression);
void print_regex(Regex_And_Flags *my_regex_and_flags);

#endif