#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "socket_wrapper.h"
#include "load_balancer.h"


int main()
{
	error_code_t status = SUCCESS_CODE;
	LoadBalancer *LB;
	srand(time(0));

	status = initialize_LB(&LB);

	if (status != SUCCESS_CODE)
		goto main_clean_up;



	char* test_msg = "GET /counter bla  \r\n\r\n";
	char msg_segment_buffer[200];
	status = send_message(LB->servers_socket[0], test_msg, strlen(test_msg));

	if (status != SUCCESS_CODE)
			goto main_clean_up;

	status = recv(LB->servers_socket[0], msg_segment_buffer, 200, 0);
	printf("msg_segment_buffer = %s\n", msg_segment_buffer);

	if (status != SUCCESS_CODE)
		goto main_clean_up;


	// recv msg from http 

	// send http msg to servers 

	// recv msg from servers 

	// send to http 




main_clean_up:
	close_socket(LB->http_socket);
	close_socket(LB->lb_socket);
	return 0;
}
