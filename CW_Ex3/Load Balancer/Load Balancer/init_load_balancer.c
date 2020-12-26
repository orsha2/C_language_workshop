
#include <stdlib.h>
#include "init_load_balancer.h"
#include "socket_wrapper.h"

static const char* HTTP_FILE_PORT_NAME = "http_port";
static const char* SERVERS_FILE_PORT_NAME = "server_port";


error_code_t write_port_to_file(const char* file_name, int port_num);
error_code_t write_occupied_ports_to_file(int http_port, int servers_port);

error_code_t initialize_load_balancer(LoadBalancer** p_LB)
{
	error_code_t status = SUCCESS_CODE;
	int server_index; 
	int http_port, servers_port;

	LoadBalancer *lb = (LoadBalancer*)malloc(sizeof(LoadBalancer));

	status = check_mem_alloc(lb, __FILE__, __LINE__, __func__);

	if (status != SUCCESS_CODE)
		return status;

	*p_LB = lb;

	status = initialize_main_socket(&(lb->lb_main_http_socket), &http_port);
	
	if (status != SUCCESS_CODE)
		return status;

	status = initialize_main_socket(&(lb->lb_main_servers_socket), &servers_port);

	if (status != SUCCESS_CODE)
		return status;

	status = write_occupied_ports_to_file(http_port, servers_port);
	
	if (status != SUCCESS_CODE)
		return status;

	lb->lb_http_socket = accept(lb->lb_main_http_socket, NULL, NULL);

	for (server_index = 0; server_index < SERVERS_NUMBER; server_index++)
	{
		lb->servers_socket[server_index] = accept(lb->lb_main_servers_socket, NULL, NULL);
	}

	
	return status;
}

error_code_t write_occupied_ports_to_file(int http_port, int servers_port)
{
	error_code_t status = SUCCESS_CODE;

	status = write_port_to_file(HTTP_FILE_PORT_NAME, http_port);

	if (status != SUCCESS_CODE)
		return status;	  

	status = write_port_to_file(SERVERS_FILE_PORT_NAME, servers_port);

	return status; 
}

error_code_t write_port_to_file(const char* file_name, int port_num)
{
	error_code_t status = SUCCESS_CODE;

	FILE* file = fopen(file_name, "w");

	status = check_file_opening(file, __FILE__, __LINE__, __func__);

	if (status != SUCCESS_CODE)
		return status;

	fprintf(file, "%d", port_num);

	if (file != NULL)
		fclose(file);

	return status;
}
