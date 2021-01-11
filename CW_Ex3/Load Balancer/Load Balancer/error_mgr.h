#ifndef ERROR_MGR_H
#define ERROR_MGR_H

#include <stdio.h>

typedef enum {
  SUCCESS_CODE,
  ARGS_NUM_ERROR,
  MEM_ALLOC_ERROR,
  FILE_OPEN_FAILED,
  SOCKET_CREATION_FAILED,
  SOCKET_LISTEN_FAILED,
  SOCKET_SEND_FAILED,
  SOCKET_RECV_FAILED,
  SOCKET_CONNECTION_CLOSED
} error_code_t;

error_code_t check_mem_alloc(void* ptr, const char* file, int line, const char* func_name);

error_code_t check_file_opening(FILE* file_ptr, const char* file, int line, const char* func_name);

error_code_t check_socket_result(int socket_result, int invalid_socket_result, error_code_t error_code,
                                 const char* file, int line, const char* func_name);

#endif
