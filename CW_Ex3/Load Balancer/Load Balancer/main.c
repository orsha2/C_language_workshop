
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "socket_wrapper.h"
#include "init_load_balancer.h"

static const char* END_OF_MSG = "\r\n\r\n";

int main()
{
	error_code_t status = SUCCESS_CODE;
	LoadBalancer *LB;
	srand(time(0));

	status = initialize_load_balancer(&LB);

	if (status != SUCCESS_CODE)
		goto main_clean_up;

	int current_handling_server = 0; 

	//----------------------------------------------------------------------------
	char* test_msg = "GET /counter bla  \r\n\r\n";
	//char msg_segment_buffer[200];
	//status = send_message(LB->servers_socket[0], test_msg, strlen(test_msg));

	//if (status != SUCCESS_CODE)
	//		goto main_clean_up;

	//status = recv(LB->servers_socket[0], msg_segment_buffer, 200, 0);
	//printf("msg_segment_buffer = %s\n", msg_segment_buffer);

	//if (status != SUCCESS_CODE)
	//	goto main_clean_up;
	//----------------------------------------------------------------------------

	char* received_msg = NULL;
	int received_msg_length=0;

	while (1) 
	{
	    // recv msg from http 
		// status =  receive_message(LB->lb_http_socket, END_OF_MSG, char** p_received_msg_buffer, int* p_received_msg_length);
		//if (status != SUCCESS_CODE)
		//	goto main_clean_up;

		status = send_message(LB->servers_socket[current_handling_server], test_msg, strlen(test_msg));

		if (status != SUCCESS_CODE)
			goto main_clean_up;
	     
		status =  receive_message(LB->servers_socket[current_handling_server], END_OF_MSG, &received_msg, &received_msg_length);

		if (status != SUCCESS_CODE)
			goto main_clean_up;

	    // send to http 
		// status = send_message(LB->lb_http_socket, test_msg, strlen(test_msg));
		//if (status != SUCCESS_CODE)
		//	goto main_clean_up;
		 printf("%s", received_msg);

		current_handling_server = (current_handling_server + 1) % SERVERS_NUMBER;
	}









main_clean_up:
	close_socket(LB->lb_main_http_socket);
	close_socket(LB->lb_main_servers_socket);
	return 0;
}
