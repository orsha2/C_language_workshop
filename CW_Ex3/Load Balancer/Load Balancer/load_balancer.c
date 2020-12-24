
#include "load_balancer.h"
#include "socket_wrapper.h"
#include "error_mgr.h"

error_code_t initialize_LB(LoadBalancer* LB); 

error_code_t initialize_LB(LoadBalancer* LB)
{
	error_code_t status = SUCCESS_CODE;
	int server_index; 
	int http_port, server_port;

	LoadBalancer *LB = (LoadBalancer*)malloc(sizeof(LoadBalancer));

	status = check_mem_alloc(LB, __FILE__, __LINE__, __func__);

	if (status != SUCCESS_CODE)
		return status;

	status = initialize_main_socket(&(LB->lb_http_socket), &http_port);

	if (status != SUCCESS_CODE)
		return status;

	status = initialize_main_socket(&(LB->lb_servers_socket), &server_port);

	if (status != SUCCESS_CODE)
		return status;

	for (server_index = 0; server_index < SERVERS_NUMBER; server_index++)
	{
		LB->servers_socket[server_index] = accept(LB->lb_servers_socket, NULL, NULL); 
	}

	return LB;
}
