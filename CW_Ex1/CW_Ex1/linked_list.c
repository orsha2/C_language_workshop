#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

const char* err_header = "ERROR: ";
const char* err_not_found = "data not found in list";
const char* err_index_out_of_range = "index out of range"; 

void add_node(Node* list, int new_data);
void print_error_and_exit(Node* list, const char* header, const char* message, int info);
Node* get_node_via_data(Node* list, int data);
Node* get_node_via_index(Node* list, int index);
Node* delete_node_and_return_next(Node* node);
int is_empty(Node* list);

Node* new_node(int data)
{
	Node* p_new_node;
	p_new_node = (Node*)malloc(sizeof(Node));

	p_new_node->next = NULL;
	p_new_node->data = data;
	return p_new_node;
}

void add_node(Node* list, int new_data)
{
	Node* p_new_node = new_node(new_data);
	p_new_node->next = list->next;
	list->next = p_new_node;
}

Node* get_node_via_data(Node* list, int data)
{
	while (list != NULL) {
		if (list->data == data)
			return list;
		list = list->next;
	}
	return NULL; 
}

Node* get_node_via_index(Node* list, int index) 
{
	int i =0;
	for (i = 0; i < index && list != NULL ;i++)
		list = list->next;

	if (list == NULL)
		print_error_and_exit(list, err_header, err_index_out_of_range, index);

	return list;
}

int get_index_via_data(Node* list, int data)
{
	int i = 0;

	while (list != NULL) {
		if (list->data == data) 
			return i;
		list = list->next;
		i++;
	}
	return -1;
}

Node* add_to_start(Node* list, int data)
{
	Node* p_new_node = new_node(data);
	if (is_empty(list))
		return p_new_node;
	
	p_new_node->next = list;
	return p_new_node;
}

Node* add_to_end(Node* list, int data)
{
	Node* p_end = list;

	if (is_empty(p_end))
		return new_node(data);
	
	while(p_end->next != NULL)
		p_end = p_end->next;

	add_node(p_end, data);
	return list;
}

Node* add_after(Node* list, int new_data, int existing_data)
{
	Node* p_existing_data_node = get_node_via_data(list, existing_data);

	if (p_existing_data_node == NULL)
		print_error_and_exit(list, err_header, err_not_found, existing_data);

	add_node(p_existing_data_node, new_data); 
	return list; 
}

int is_empty(Node* list)
{
	return (list == NULL);
}

Node* del_node_at_index(Node* list, int index)
{
	Node* node_to_delete = get_node_via_index(list, index);
	Node* next_node = delete_node_and_return_next(node_to_delete);

	if (index == 0)
		return next_node;

	Node* prev_node = get_node_via_index(list, index-1);
	prev_node->next = next_node;
	return list;
}

Node* delete_node_and_return_next(Node* node)
{
	Node* next_node = node->next;
	free(node);
	return next_node;
}

void free_list(Node* list)
{
	while (list != NULL)
		list = delete_node_and_return_next(list);
}

void print_list(Node* list)
{
	if (is_empty(list)) {
		printf("[]\n");
		return;
	}

	printf("[%d", list->data);
	list = list->next;

	while (list != NULL) {
		printf(", %d", list->data);
		list = list->next;
	}
	printf("]\n");
}

void print_error_and_exit(Node* list, const char* header, const char* message, int info)
{
	printf("%s %s (%d)\n", header, message, info);
	free_list(list);
	exit(1);
}
