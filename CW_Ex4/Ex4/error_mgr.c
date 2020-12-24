
#include "error_mgr.h"
#include <stdio.h>
#include <stdlib.h>


const char *MSG_ERR_CANNOT_OPEN_FILE = "Couldn't open file";
const char *MSG_ERR_MEM_ALLOC = "Memory allocation error";

void print_error(const char *msg, const char *file, int line, const char *func_name);


void print_error(const char *msg, const char *file, int line, const char *func_name)
{
  printf("ERROR: %s\n", msg);
  printf("File: %s\n", file);
  printf("Line: %d, Function: %s\n", line, func_name);
}

Error_Code_t check_mem_alloc(void *ptr, const char *file, int line, const char *func_name)
{
  if (ptr == NULL) {
    print_error(MSG_ERR_MEM_ALLOC, file, line, func_name);
    return MEM_ALLOC_ERROR;
  }
  return SUCCESS_CODE;
}

Error_Code_t check_file_opening(FILE *file_ptr, const char *file, int line, const char *func_name)
{
  if (file_ptr == NULL) {
    print_error(MSG_ERR_CANNOT_OPEN_FILE, file, line, func_name);
    return FILE_OPEN_FAILED;
  }
  return SUCCESS_CODE;
}

