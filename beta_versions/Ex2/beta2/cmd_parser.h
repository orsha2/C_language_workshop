#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include "init_regex.h"

Error_Code_t parse_cmd_args(int arg_num, char **args, Regex_And_Flags **p_regex_and_flags, char **p_expression,
                            char **p_file_name);

#endif
