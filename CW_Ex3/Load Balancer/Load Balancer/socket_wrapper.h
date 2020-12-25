#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H 


//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib")
//#pragma warning(disable:4996) 

//Linux
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
//Linux

#include "error_mgr.h"

error_code_t initialize_main_socket(int* p_socket, int* p_socket_port); 
error_code_t send_message(int socket, char* msg, int msg_size);

void close_socket(int socket);


#endif