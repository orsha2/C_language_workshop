#ifndef UI_H 
#define UI_H
#include "linked_list.h" 

void parser(char* cmd, int* arg1, int* arg2);
Node* run(Node* list, char* cmd, int arg1, int arg2);

#endif