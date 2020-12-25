#ifndef ERROR_MGR_H
#define ERROR_MGR_H

#include <stdio.h>

typedef enum {  
	SUCCESS_CODE,
	ARGS_NUM_ERROR,
	MEM_ALLOC_ERROR,
	FILE_OPEN_FAILED,
	SOCKET_SEND_FAILED,
	SOCKET_RECV_FAILED,
	SOCKET_CLOSED_CONNECTION,
	SOCKET_FAILED,
	LISTEN_FAILED,
	LISTEN_SUCCESS,
} error_code_t;

extern const char *MSG_ERR_MEM_ALLOC;
extern const char *MSG_ERR_CANNOT_OPEN_FILE;

error_code_t check_mem_alloc(void *ptr, const char *file, int line, const char *func_name);
error_code_t check_file_opening(FILE *file_ptr, const char *file, int line, const char *func_name);

#endif
