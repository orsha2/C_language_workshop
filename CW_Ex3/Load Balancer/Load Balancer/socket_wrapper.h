#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H 

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#include <string.h>
#include "error_mgr.h"

error_code_t initialize_main_socket(int* p_socket, int* p_socket_port); 
error_code_t receive_message(int communication_socket,const char* end_of_msg, char** p_received_msg_buffer, int* p_received_msg_length);
error_code_t send_message(int communication_socket, char* msg, int msg_size);
void close_socket(int socket);


#endif
