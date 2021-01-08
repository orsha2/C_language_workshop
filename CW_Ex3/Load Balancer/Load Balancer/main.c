#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "init_load_balancer.h"
#include "socket_wrapper.h"

#define END_OF_MSG "\r\n\r\n"
#define END_OF_MSG_LENGTH 4

void free_main_resources(LoadBalancer* p_lb);


int main()
{
  error_code_t status = SUCCESS_CODE;
  LoadBalancer LB;
  int current_handling_server = 0;
  char* received_msg = NULL;
  int received_msg_length = 0;
  srand(time(0));

  status = initialize_load_balancer(&LB);

  if (status != SUCCESS_CODE) {
    goto main_clean_up;
  }

  while (true) {
    status = receive_message(LB.lb_http_socket, END_OF_MSG, END_OF_MSG_LENGTH, &received_msg, &received_msg_length);

    if (status == SOCKET_CONNECTION_CLOSED) {
      LB.lb_http_socket = accept(LB.lb_main_http_socket, NULL, NULL);
      continue;
    }

    if (status != SUCCESS_CODE) {
      goto main_clean_up;
    }

    status = send_message(LB.servers_socket[current_handling_server], received_msg, received_msg_length);

    if (status != SUCCESS_CODE) {
      goto main_clean_up;
    }

    status = receive_message(LB.servers_socket[current_handling_server], END_OF_MSG, END_OF_MSG_LENGTH, &received_msg,
                             &received_msg_length);

    if (status != SUCCESS_CODE) {
      goto main_clean_up;
    }

    status = send_message(LB.lb_http_socket, received_msg, received_msg_length);
    if (status != SUCCESS_CODE) {
      goto main_clean_up;
    }

    current_handling_server = (current_handling_server + 1) % SERVERS_NUMBER;
  }

main_clean_up:
  free_main_resources(&LB);
  return 0;
}

void free_main_resources(LoadBalancer* p_lb)
{
  close(p_lb->lb_main_http_socket);
  close(p_lb->lb_main_servers_socket);

  int server_index;
  for (server_index = 0; server_index < SERVERS_NUMBER; server_index++) {
    close(p_lb->lb_main_servers_socket);
  }
}
