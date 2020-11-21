#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <stdlib.h>

error_code_t parse_cmd_args(int arg_num, char** args, regex_and_flags** expression_and_flags, char** p_file_name);



#endif
