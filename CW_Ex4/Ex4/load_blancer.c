# include "load_balancer.h"

LoadBalancer* initialize_loadBalancer();
int initialize_socket();

LoadBalancer* initialize_loadBalancer()
{
	int server_index;

	LoadBalancer *LB = (LoadBalancer*)malloc(sizeof(LoadBalancer));
	LB->http_socket = initialize_socket(HTTP);
	LB->lb_socket = initialize_socket(SERVER);

	for (server_index = 0; server_index < SERVERS_NUMBER; server_index++) {
		//LB->servers_socket[server_index] = ();
	}

	return LB;
}


