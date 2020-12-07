#ifndef ERROR_MGR_H
#define ERROR_MGR_H

#include <stdio.h>

typedef enum { SUCCESS_CODE, ARGS_NUM_ERROR, MEM_ALLOC_ERROR, FILE_OPEN_FAILED } Error_Code_t;

extern const char *MSG_ERR_NUM_ARGS;
extern const char *MSG_ERR_CANNOT_OPEN_FILE;
extern const char *MSG_ERR_MEM_ALLOC;

Error_Code_t check_mem_alloc(void *ptr, const char *file, int line, const char *func_name);
Error_Code_t check_file_opening(FILE *file_ptr, const char *file, int line, const char *func_name);
Error_Code_t check_argc_value_range(int argc);

#endif
