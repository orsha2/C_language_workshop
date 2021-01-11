#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "init_load_balancer.h"
#include "socket_wrapper.h"

#define END_OF_MSG "\r\n\r\n"
#define END_OF_MSG_LENGTH 4

error_code_t balance_load_between_servers(LoadBalancer* LB);
void free_main_resources(LoadBalancer* p_LB);


int main()
{
  error_code_t status = SUCCESS_CODE;
  LoadBalancer LB;
  srand(time(0));

  status = initialize_load_balancer(&LB);

  if (status == SUCCESS_CODE) {
    balance_load_between_servers(&LB);
  }

  free_main_resources(&LB);
  return (int)status;
}

error_code_t balance_load_between_servers(LoadBalancer* p_LB)
{
  error_code_t status = SUCCESS_CODE;

  int current_handling_server = 0;
  char* received_msg = NULL;
  int received_msg_length = 0;

  while (true) {
    status = receive_message(p_LB->lb_http_socket, END_OF_MSG, END_OF_MSG_LENGTH, &received_msg, &received_msg_length);

    if (status == SOCKET_CONNECTION_CLOSED) {
      close(p_LB->lb_http_socket);
      p_LB->lb_http_socket = accept(p_LB->lb_main_http_socket, NULL, NULL);
      continue;
    }

    if (status != SUCCESS_CODE) {
      goto balance_load_between_servers_exit;
    }
    status = send_message(p_LB->servers_socket[current_handling_server], received_msg, received_msg_length);

    if (status != SUCCESS_CODE) {
      goto balance_load_between_servers_exit;
    }
    status = receive_message(p_LB->servers_socket[current_handling_server], END_OF_MSG, END_OF_MSG_LENGTH, &received_msg,
                             &received_msg_length);

    if (status != SUCCESS_CODE) {
      goto balance_load_between_servers_exit;
    }
    status = send_message(p_LB->lb_http_socket, received_msg, received_msg_length);

    if (status != SUCCESS_CODE) {
      goto balance_load_between_servers_exit;
    }
    current_handling_server = (current_handling_server + 1) % SERVERS_NUMBER;
  }

balance_load_between_servers_exit:

  if (received_msg != NULL)
    free(received_msg);

  return status;
}

void free_main_resources(LoadBalancer* p_LB)
{
  if (p_LB->lb_main_http_socket != SOCKET_ERROR) {
    close(p_LB->lb_main_http_socket);
  }

  if (p_LB->lb_main_servers_socket != SOCKET_ERROR) {
    close(p_LB->lb_main_servers_socket);
  }

  if (p_LB->lb_http_socket != SOCKET_ERROR) {
      close(p_LB->lb_http_socket);
  }

  int server_index;
  for (server_index = 0; server_index < SERVERS_NUMBER; server_index++) {
    if (p_LB->servers_socket[server_index] != SOCKET_ERROR) {
      close(p_LB->servers_socket[server_index]);
    }
  }
}
