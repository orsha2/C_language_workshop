#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "socket_wrapper.h"
#include "init_load_balancer.h"

void free_main_resources(LoadBalancer* p_lb); 
 
static const char* END_OF_MSG = "\r\n\r\n";
static const char* END_OF_MSG_LENGTH = 4;


int main()
{
	error_code_t status = SUCCESS_CODE;
	LoadBalancer LB;
	int current_handling_server = 0;
	char* received_msg = NULL;
	int received_msg_length = 0;
	srand(time(0));

	status = initialize_load_balancer(&LB);

	if (status != SUCCESS_CODE) 
	{
		goto main_clean_up;
	}

	while (1) 
	{ 
		status =  receive_message(LB.lb_http_socket, END_OF_MSG, END_OF_MSG_LENGTH, &received_msg, &received_msg_length);
		if (status != SUCCESS_CODE)
			goto main_clean_up;

		status = send_message(LB.servers_socket[current_handling_server], received_msg, received_msg_length);

		if (status != SUCCESS_CODE)
			goto main_clean_up;
	     
		status =  receive_message(LB.servers_socket[current_handling_server], END_OF_MSG, END_OF_MSG_LENGTH, &received_msg, &received_msg_length);

		if (status != SUCCESS_CODE)
			goto main_clean_up;
	        
		status = send_message(LB.lb_http_socket, received_msg, received_msg_length);
		if (status != SUCCESS_CODE)
			goto main_clean_up;
		
		current_handling_server = (current_handling_server + 1) % SERVERS_NUMBER;
	}

main_clean_up:
	free_main_resources(&LB);
	close_socket(LB.lb_main_http_socket);
	close_socket(LB.lb_main_servers_socket);
	return 0;
}

void free_main_resources(LoadBalancer* p_lb)
{
	close_socket(p_lb->lb_main_http_socket);
	close_socket(p_lb->lb_main_servers_socket);

	for (server_index = 0; server_index < SERVERS_NUMBER; server_index++)
	{
		close_socket(p_lb->lb_main_servers_socket);
	}
}