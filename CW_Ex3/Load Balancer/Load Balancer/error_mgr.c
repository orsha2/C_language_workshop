
#include "error_mgr.h"
#include <stdio.h>
#include <stdlib.h>

const char *MSG_ERR_CANNOT_OPEN_FILE = "Couldn't open file";
const char *MSG_ERR_MEM_ALLOC = "Memory allocation error";
const char *MSG_ERR_SOCKET_CREATION_FAILED = "Socket creation failed";
const char *MSG_ERR_SOCKET_LISTEN_FAILED = "Socket listen creation failed";
const char *MSG_ERR_SOCKET_SEND_FAILED = "Socket send creation failed";

void print_error(const char *msg, const char *file, int line, const char *func_name);

void print_error(const char *msg, const char *file, int line, const char *func_name)
{
  printf("ERROR: %s\n", msg);
  printf("File: %s\n", file);
  printf("Line: %d, Function: %s\n", line, func_name);
}

error_code_t check_mem_alloc(void *ptr, const char *file, int line, const char *func_name)
{
  if (ptr == NULL) {
    print_error(MSG_ERR_MEM_ALLOC, file, line, func_name);
    return MEM_ALLOC_ERROR;
  }
  return SUCCESS_CODE;
}

error_code_t check_file_opening(FILE *file_ptr, const char *file, int line, const char *func_name)
{
  if (file_ptr == NULL) {
    print_error(MSG_ERR_CANNOT_OPEN_FILE, file, line, func_name);
    return FILE_OPEN_FAILED;
  }
  return SUCCESS_CODE;
}

error_code_t check_socket_creation_result(int new_socket, int invalid_socket_value, const char *file, int line,
                                          const char *func_name)
{
  if (new_socket == invalid_socket_value) {
    print_error(MSG_ERR_SOCKET_CREATION_FAILED, file, line, func_name);
    return SOCKET_CREATION_FAILED;
  }
  return SUCCESS_CODE;
}

error_code_t check_socket_listen_result(int listen_result, const char *file, int line, const char *func_name)
{
  if (listen_result != SUCCESS_CODE) {
    print_error(MSG_ERR_SOCKET_LISTEN_FAILED, file, line, func_name);
    return SOCKET_LISTEN_FAILED;
  }
  return SUCCESS_CODE;
}

error_code_t check_socket_send_result(int send_result, int invalid_send_result, const char *file, int line,
                                      const char *func_name)
{
  if (send_result == invalid_send_result) {
    print_error(MSG_ERR_SOCKET_SEND_FAILED, file, line, func_name);
    return SOCKET_SEND_FAILED;
  }
  return SUCCESS_CODE;
}
