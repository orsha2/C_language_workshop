#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#define SERVERS_NUMBER 3

#include "error_mgr.h"

typedef struct _loadBalancer {
	int lb_socket;
	int http_socket;
	int servers_socket[SERVERS_NUMBER];
}LoadBalancer;

error_code_t initialize_LB(LoadBalancer** LB);

#endif  



