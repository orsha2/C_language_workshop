
#include "error_mgr.h"
#include <stdio.h>
#include <stdlib.h>

char* ERR_MSG[] = {
  "SUCCESS!",

  "Args - wrong amount of arguments."
  "Memory - allocation error.",
  "File - opening failed.",

  "Socket - creation failed",
  "Socket - listen failed",
  "Socket - send failed.",
  "Socket - recv failed.",
  "Socket - connection closed.",
};

void print_error(error_code_t error_code, const char *file, int line, const char *func_name);

void print_error(error_code_t error_code, const char *file, int line, const char *func_name)
{
  printf("ERROR: %s\n", ERR_MSG[error_code]);
  printf("File: %s\n", file);
  printf("Line: %d, Function: %s\n", line, func_name);
}

error_code_t check_mem_alloc(void *ptr, const char *file, int line, const char *func_name)
{
  if (ptr == NULL) {
    print_error(MEM_ALLOC_ERROR, file, line, func_name);
    return MEM_ALLOC_ERROR;
  }
  return SUCCESS_CODE;
}

error_code_t check_file_opening(FILE *file_ptr, const char *file, int line, const char *func_name)
{
  if (file_ptr == NULL) {
    print_error(FILE_OPEN_FAILED, file, line, func_name);
    return FILE_OPEN_FAILED;
  }
  return SUCCESS_CODE;
}

error_code_t check_socket_result(int socket_result, int invalid_socket_result, error_code_t error_code, 
                                 const char* file, int line, const char* func_name)
{
    if (socket_result == invalid_socket_result) {
        print_error(error_code, file, line, func_name);
        return error_code;
    }
    return SUCCESS_CODE;
}
