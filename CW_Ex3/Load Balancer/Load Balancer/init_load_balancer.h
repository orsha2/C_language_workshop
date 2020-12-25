#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#define SERVERS_NUMBER 1 

#include "error_mgr.h"

typedef enum _socket_arg 
{ 
	HTTP,
	SERVER,
} socket_arg;

typedef struct _loadBalancer {
	int lb_main_servers_socket;
	int lb_main_http_socket;
	int lb_http_socket;
	int servers_socket[SERVERS_NUMBER];
}LoadBalancer;

error_code_t initialize_LB(LoadBalancer** LB);

#endif  



