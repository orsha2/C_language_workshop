
#include "socket_wrapper.h"
#include <stdlib.h>
#include "error_mgr.h"
#define MSG_SEGMENT_SIZE 32

typedef enum _bind_status
{ 
	BIND_SUCCESS = 0 ,
	BIND_FAILED
}bind_status;




static const char* LOCAL_HOST = "127.0.0.1";
static const int  MAX_QUEUE_PENDING_CONNETIONS = 10;
static const int LOWER_PORT_LIMIT = 1023;
static const int UPPER_PORT_LIMIT = 63999;


int bind_to_free_port(int socket);
error_code_t listen_to_port_connections(int main_socket);
struct sockaddr_in initialize_sockaddr(const char* str_ip, int port);
int get_random_number(int lower_limit, int upper_limit);
error_code_t check_socket_listen_result(int listen_result);


error_code_t initialize_main_socket(int* p_socket, int* p_socket_port)
{
	error_code_t status = SUCCESS_CODE;
	int new_socket;

	new_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (new_socket == -1)
		return SOCKET_FAILED;

	*p_socket_port = bind_to_free_port(new_socket);

	status = listen_to_port_connections(new_socket);

	*p_socket = new_socket;

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

		bind_status = bind(socket, (struct sockaddr *)&service, sizeof(service));
	}

	printf("port = %d \n", port);
	return port;
}

error_code_t listen_to_port_connections(int main_socket)
{
	error_code_t status = SUCCESS_CODE; 

	int listen_result;

	listen_result = listen(main_socket, MAX_QUEUE_PENDING_CONNETIONS);

	status = check_socket_listen_result(listen_result);

	return status;
	
}

error_code_t check_socket_listen_result(int listen_result)
{
	if (listen_result != SUCCESS_CODE)
		return LISTEN_FAILED;
	return SUCCESS_CODE;
}

struct sockaddr_in initialize_sockaddr(const char* str_ip, int port)
{
	struct sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(str_ip);
	service.sin_port = htons(port);

	return service;
}

int get_random_number(int lower_limit, int upper_limit)
{
	int domain = upper_limit - lower_limit + 1;
	return lower_limit + (rand() % domain);
}

void close_socket(int socket)
{
	//shutdown(socket, SD_BOTH);
	// Linux 
	shutdown(socket, SHUT_RDWR);
	// Linux
	close(socket);
}

error_code_t send_message(int socket, char* msg, int msg_size)
{

	int total_bytes_sent =  0;

	while (total_bytes_sent < msg_size)
	{
		total_bytes_sent += send(socket, msg , msg_size - total_bytes_sent, 0);

		/*if (total_bytes_sent == SOCKET_ERROR) {
			return SOCKET_SEND_FAILED;
		}*/

	    // LINUX
		if (total_bytes_sent == SO_ERROR) {
			return SOCKET_SEND_FAILED;
		}
		// LINUX

		msg += total_bytes_sent;
	
	}
	return SUCCESS_CODE;
}

//error_code_t receive_message(int com_socket, char* end_of_msg, char** p_received_msg_buffer, int *p_received_msg_length)
//{
//	error_code_t status = SUCCESS_CODE;
//
//	char* received_msg_buffer = NULL;
//	int msg_length = 0;
//
//	char* msg_segment_buffer[MSG_SEGMENT_SIZE];
//	int bytes_recv = 0;
//
//	do {
//		status = receive_message_segment(com_socket, msg_segment_buffer, &bytes_recv);
//
//		if (status != SUCCESS_CODE)
//			return status; 
//
//		status = change_buffer_size(received_msg_buffer, msg_length + bytes_recv);
//
//		if (status != SUCCESS_CODE)
//			return status;
//
//		append_segment_to_msg_buffer(received_msg_buffer, &msg_length, msg_segment_buffer, bytes_recv);
//
//	} while (not_end_of_msg(received_msg_buffer, msg_length, end_of_msg));
//	
//	*p_received_msg_buffer = received_msg_buffer;
//	*p_received_msg_length = msg_length; 
//
//	return status;
//}
//
//error_code_t change_buffer_size(char* buffer, int new_size) 
//{
//	error_code_t status = SUCCESS_CODE;
//
//	buffer = (char*)realloc(buffer, new_size);
//
//	status = check_mem_alloc(buffer, __FILE__, __LINE__, __func__);
//
//	return status;
//}
//
//error_code_t receive_message_segment(int com_socket, char* msg_segment_buffer, int* p_bytes_recv)
//{
//	int bytes_recv;
//
//	bytes_recv = recv(com_socket, msg_segment_buffer, MSG_SEGMENT_SIZE, 0);
//
//	if (bytes_recv == SOCKET_ERROR) {
//		return SOCKET_RECV_FAILED;
//	}
//
//	if (bytes_recv == 0) {
//		return SOCKET_CLOSED_CONNECTION;
//	}
//
//	*p_bytes_recv = bytes_recv;
//
//	return SUCCESS_CODE; 
//}
//
//void append_segment_to_msg_buffer(char* received_msg, int* p_current_msg_length, char* msg_segment_buffer, int bytes_recv)
//{
//	int current_msg_length = *p_current_msg_length;
//
//	for (size_t i = 0; i < bytes_recv; i++)
//	{
//		received_msg[current_msg_length + i] = msg_segment_buffer[i];
//	}
//
//	*p_current_msg_length += bytes_recv;
//
//}



//not_end_of_msg(char* received_msg_buffer, int current_msg_length, char* end_of_msg)
//{
//
//
//
//}


// --------------------------------------------------------------------------------------------------------------------------------------------
//
//error_code_t initialize_winsock()
//{
//	error_code_t status = SUCCESS_CODE;
//
//	WSADATA wsa_data;
//
//	int winsock_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
//
//	status = check_winsock_result(winsock_result, INITIALIZATION);
//
//	return status;
//}
//
//error_code_t deinitialize_winsock()
//{
//	error_code_t status = SUCCESS_CODE;
//
//	int winsock_result = WSACleanup();
//
//	status = check_winsock_result(winsock_result, INITIALIZATION);
//
//	return status;
//}
//
//error_code_t check_winsock_result(int winsock_result, winsock_operation winsock_op)
//{
//	error_code_t status = SUCCESS_CODE;
//	char* err_msg = NULL;
//
//	if (winsock_result != 0)
//	{
//		switch (winsock_op)
//		{
//		case INITIALIZATION:
//			err_msg = MSG_ERR_WINSOCK_INITIALIZATION_FAILED;
//			status = WINSOCK_INITIALIZATION_FAILED;
//			break;
//
//		case DEINITIALIZATION:
//			err_msg = MSG_ERR_WINSOCK_INITIALIZATION_FAILED;
//			status = WINSOCK_INITIALIZATION_FAILED;
//			break;
//		}
//		print_error(err_msg, __FILE__, __LINE__, __func__);
//	}
//	return status;
//}
