#ifndef UI_H 
#define UI_H
#include "linked_list.h" 

char* parser(char* p_cmd_line, int* arg1, int* arg2);
Node* run(Node* list, const char* cmd, int arg1, int arg2);

#endif