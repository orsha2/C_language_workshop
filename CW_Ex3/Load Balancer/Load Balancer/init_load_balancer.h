#ifndef INIT_LOAD_BALANCER_H
#define INIT_LOAD_BALANCER_H

#define SERVERS_NUMBER 1

#include "error_mgr.h"

typedef struct _loadBalancer {
  int lb_main_servers_socket;
  int lb_main_http_socket;

  int lb_http_socket;
  int servers_socket[SERVERS_NUMBER];
} LoadBalancer;

error_code_t initialize_load_balancer(LoadBalancer* p_LB);
#endif
