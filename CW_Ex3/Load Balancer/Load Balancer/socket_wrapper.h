#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "error_mgr.h"

#define SOCKET_ERROR -1

error_code_t initialize_main_socket(int* p_socket, int* p_socket_port);

error_code_t send_message(int communication_socket, char* msg, int msg_size);
error_code_t receive_message(int communication_socket, const char* end_of_msg, int end_of_msg_length,
                             char** p_received_msg_buffer, int* p_received_msg_length);

#endif
