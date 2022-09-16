//This header file consists of all variables and functions to be used through out
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node // defining a struct for all nodes
{
    int coordinates[1][1];
    int possible_arr[8]; // 8 types of directions [W , NW , N , NE , E , SE , S , SW]
    int explored_arr[8];
};

#define MAX_STACK 50    //variables for stack
int top = -1 ;
struct node node[100];
int checkpoint_stack[MAX_STACK];
int no_of_nodes ;
int dir ; ///////////////////////////////////////////////////////////////////////////////// (pending) we need to create a function which takes the current dir and then updates the possible arr and explored arr for the node
int current_node ;


#endif