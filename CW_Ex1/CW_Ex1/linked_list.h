#ifndef LINKED_LIST_H 
#define LINKED_LIST_H

typedef struct _Node {
	int data;
	struct _Node* next;
} Node;

Node* add_to_start(Node* list, int data);
Node* add_to_end(Node* list, int data);
Node* add_after(Node* list, int new_data, int existing_data);
Node* del_node_at_index(Node* list, int index);
int get_index_via_data(Node* list, int data);
void free_list(Node* list);
void print_list(Node* list);


#endif
