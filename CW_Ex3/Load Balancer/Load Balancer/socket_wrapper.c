// ----------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include "error_mgr.h"

#define MSG_SEGMENT_SIZE 32

typedef enum _bind_status { BIND_SUCCESS = 0, BIND_FAILED};

static const char* LOCAL_HOST = "127.0.0.1";

static const int  MAX_QUEUE_PENDING_CONNETIONS = 10;

static const int LOWER_PORT_LIMIT = 1023;
static const int UPPER_PORT_LIMIT = 65000;


error_code_t initialize_main_socket(int* p_socket, int* p_socket_port)
{
	error_code_t status = SUCCESS_CODE;

	*p_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

	*p_socket_port = bind_to_free_port(*p_socket);

	status = listen_to_port_connections(*p_socket, MAX_QUEUE_PENDING_CONNETIONS);

	return status;
}

int bind_to_free_port(int socket) 
{
	int bind_status = BIND_FAILED;
	int port;
	struct sockaddr_in service;
	
	while (bind_status != BIND_SUCCESS)
	{
		port = get_random_number(LOWER_PORT_LIMIT, UPPER_PORT_LIMIT);
		
		service = initialize_sockaddr(LOCAL_HOST, port);

		bind_status = bind(socket, (SOCKADDR*) & service, sizeof(service));
	}

	return port;
}

error_code_t listen_to_port_connections(int main_socket, int backlog)
{
	error_code_t status = SUCCESS_CODE; 

	int listen_result;

	listen_result = listen(main_socket, MAX_QUEUE_PENDING_CONNETIONS);

	status = check_socket_listen_result(listen_result);

	return status;
	
}

error_code_t send_message(int com_socket, char* msg_buffer, int msg_size)
{

	int total_bytes_sent = 0;
	int bytes_sent;

	while (total_bytes_sent < msg_size)
	{
		bytes_sent = send(com_socket, msg_buffer, msg_size, 0);

		if (bytes_sent == SOCKET_ERROR) {
			return SOCKET_SEND_FAILED;
		}

		total_bytes_sent += bytes_sent;
	}

	return SUCCESS_CODE;
}

error_code_t receive_message(int com_socket, char* end_of_msg, char** p_received_msg_buffer, int *p_received_msg_length)
{
	error_code_t status = SUCCESS_CODE;

	char* received_msg_buffer = NULL;
	int msg_length = 0;

	char* msg_segment_buffer[MSG_SEGMENT_SIZE];
	int bytes_recv = 0;

	do {
		status = receive_message_segment(com_socket, msg_segment_buffer, &bytes_recv);

		if (status != SUCCESS_CODE)
			return status; 

		status = change_buffer_size(received_msg_buffer, msg_length + bytes_recv);

		if (status != SUCCESS_CODE)
			return status;

		append_segment_to_msg_buffer(received_msg_buffer, &msg_length, msg_segment_buffer, bytes_recv);

	} while (not_end_of_msg(received_msg_buffer, msg_length, end_of_msg));
	
	*p_received_msg_buffer = received_msg_buffer;
	*p_received_msg_length = msg_length; 

	return status;
}

error_code_t change_buffer_size(char* buffer, int new_size) 
{
	error_code_t status = SUCCESS_CODE;

	buffer = (char*)realloc(buffer, new_size);

	status = check_mem_alloc(buffer, __FILE__, __LINE__, __func__);

	return status;
}

error_code_t receive_message_segment(int com_socket, char* msg_segment_buffer, int* p_bytes_recv)
{
	int bytes_recv;

	bytes_recv = recv(com_socket, msg_segment_buffer, MSG_SEGMENT_SIZE, 0);

	if (bytes_recv == SOCKET_ERROR) {
		return SOCKET_RECV_FAILED;
	}

	if (bytes_recv == 0) {
		return SOCKET_CLOSED_CONNECTION;
	}

	*p_bytes_recv = bytes_recv;

	return SUCCESS_CODE; 
}

void append_segment_to_msg_buffer(char* received_msg, int* p_current_msg_length, const char* msg_segment_buffer, int bytes_recv)
{
	int current_msg_length = *p_current_msg_length;

	for (size_t i = 0; i < bytes_recv; i++)
	{
		received_msg[current_msg_length + i] = msg_segment_buffer[i];
	}

	*p_current_msg_length += bytes_recv;

}


not_end_of_msg(char* received_msg_buffer, int current_msg_length, char* end_of_msg)
{



}

struct sockaddr_in initialize_sockaddr(char* str_ip, int port)
{
	struct sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(str_ip);
	service.sin_port = htons(port);

	return service;
}

int get_random_number(int lower_limit, int upper_limit) 
{	
	int random_num = (lower_limit + (rand() % (upper_limit - lower_limit + 1)));

	return random_num; 
}






// --------------------------------------------------------------------------------------------------------------------------------------------

error_code_t initialize_winsock()
{
	error_code_t status = SUCCESS_CODE;

	WSADATA wsa_data;

	int winsock_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);

	status = check_winsock_result(winsock_result, INITIALIZATION);

	return status;
}

error_code_t deinitialize_winsock()
{
	error_code_t status = SUCCESS_CODE;

	int winsock_result = WSACleanup();

	status = check_winsock_result(winsock_result, INITIALIZATION);

	return status;
}

error_code_t check_winsock_result(int winsock_result, winsock_operation winsock_op)
{
	error_code_t status = SUCCESS_CODE;
	char* err_msg = NULL;

	if (winsock_result != 0)
	{
		switch (winsock_op)
		{
		case INITIALIZATION:
			err_msg = MSG_ERR_WINSOCK_INITIALIZATION_FAILED;
			status = WINSOCK_INITIALIZATION_FAILED;
			break;

		case DEINITIALIZATION:
			err_msg = MSG_ERR_WINSOCK_INITIALIZATION_FAILED;
			status = WINSOCK_INITIALIZATION_FAILED;
			break;
		}
		print_error(err_msg, __FILE__, __LINE__, __func__);
	}
	return status;
}