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

void push(int node);    //function prototyping 
int pop() ;
bool is_new_node(int obtained_coordinates[1][1] ) ;

//--------------------------------------------------------------------------------//

//main() starts from here 
int main()
{
    
    int * adj_list [50] ;
    int * adj_dist_list [50] ;
    int obtained_coordinates[1][1] ;

    adj_list[no_of_nodes] = (int *) malloc ( sizeof(int[4])) ;      //To store all the nearest neighbour
    adj_dist_list[no_of_nodes] = (int *) malloc ( sizeof(int[4])) ;         //To store the respective distances

}
//main() ends here

//--------------------------------------------------------------------------------//

bool is_new_node(int obtained_coordinates[1][1])
{
    for (int i = 0; i < no_of_nodes; i++)
    {
        if (obtained_coordinates[0][0] == node[i].coordinates[0][0]) // comparing with all available coordinates of previous unique nodes
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
//is_new_node of function

void push(int node)
{
    if (top > MAX_STACK)
    {
        printf("Stack overflow") ;
    }
    else
    {
        checkpoint_stack[++top] = node;
    }
}
//push() ends here

int pop()
{
    if(top == -1 )
    {
        printf("Maze has ended") ;
        exit(0);
        /////////////////////////////////////////////////////////////////////////////////////////Maze has ended --> Add code to go END ( pending )
    }
    else
    {
        return checkpoint_stack[top--] ;
    }
}
//pop() ends here
