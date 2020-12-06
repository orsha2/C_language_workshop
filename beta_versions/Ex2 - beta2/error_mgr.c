#include <stdio.h>
#include <stdlib.h>
#include "error_mgr.h" 

const char *MSG_ERR_NUM_ARGS = "wrong amount of arguments";
const char *MSG_ERR_CANNOT_OPEN_FILE = "couldn't open file";
const char *MSG_ERR_MEM_ALLOC = "memory allocation error";

void print_error(const char *msg, const char *file, int line, const char *func_name)
{
  printf("ERROR: %s\n", msg);
  printf("File: %s\n", file);
  printf("Line: %d, Function: %s\n", line, func_name);
}

Error_Code_t check_mem_alloc(void* ptr, const char* file, int line, const char* func_name)
{
    if (ptr == NULL)
    {
        print_error(MSG_ERR_MEM_ALLOC, file, line, func_name);
        return MEM_ALLOC_ERROR;
    }
    return SUCCESS_CODE;
}