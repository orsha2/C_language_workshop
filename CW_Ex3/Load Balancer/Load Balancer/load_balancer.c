#include "load_balancer.h"
#include "socket_wrapper.h"

#include <stdlib.h>

error_code_t initialize_LB(LoadBalancer** LB)
{
	error_code_t status = SUCCESS_CODE;
	int server_index; 
	int http_port, server_port;

	LoadBalancer *lb = (LoadBalancer*)malloc(sizeof(LoadBalancer));

	status = check_mem_alloc(lb, __FILE__, __LINE__, __func__);

	if (status != SUCCESS_CODE) {
		return status;
	}

	status = initialize_main_socket(&(lb->http_socket), &http_port);
	

	if (status != SUCCESS_CODE) {
		return status;
	}

	status = initialize_main_socket(&(lb->lb_socket), &server_port);

	if (status != SUCCESS_CODE){
		return status;
	}

	for (server_index = 0; server_index < SERVERS_NUMBER; server_index++)
	{
		lb->servers_socket[server_index] = accept(lb->lb_socket, NULL, NULL);
	}

	*LB = lb;

	return status;
}
