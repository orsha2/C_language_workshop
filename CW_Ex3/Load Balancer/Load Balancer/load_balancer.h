#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#define SERVERS_NUMBER 3


typedef enum _socket_arg { HTTP, SERVER } socket_arg;

typedef struct _loadBalancer {
	int lb_servers_socket;
	int lb_http_socket;
	int servers_socket[SERVERS_NUMBER];
}LoadBalancer;


#endif  



