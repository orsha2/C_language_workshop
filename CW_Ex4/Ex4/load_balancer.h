#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#define SERVERS_NUMBER 3


enum SOCKET_ARGUMENT { HTTP, SERVER };


typedef struct _loadBalancer {
	int lb_socket;
	int http_socket;
	int servers_socket[SERVERS_NUMBER];
}LoadBalancer;

enum week{Mon, Tue, Wed};

#endif  



