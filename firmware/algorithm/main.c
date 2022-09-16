#include "variable.h" 

void push(int node);    //function prototyping 
int pop() ;
bool is_new_node(int obtained_coordinates[1][1] ) ;
int check_explored () ;

//--------------------------------------------------------------------------------//

//main() starts from here 
int main()
{ 
    int * adj_list [50] ;
    int * adj_dist_list [50] ;
    int obtained_coordinates[1][1] ;

    adj_list[no_of_nodes] = (int *) malloc ( sizeof(int[4])) ;      //To store all the nearest neighbour
    adj_dist_list[no_of_nodes] = (int *) malloc ( sizeof(int[4])) ;         //To store the respective distances
    printf("yay") ;
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
//is_new_node() ends here

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

int check_explored ()
{
    int flag = 0 ;
    int i ;

    for (i = 0 ; i < 8 ; i++)
    {
        if (node[current_node].possible_arr[i] == node[current_node].explored_arr[i] )
        {
            continue ;
        }
        else
        {
            flag = 1 ;
            break ;
        }
    }

    if ( flag == 0)
    {
        int x ;
        x =pop() ; //will pop the node , since it is completely explored
        printf("Node %d explored completely\n" , x ) ; 
    }
    else
    {
        printf("still exploring the node %d\n" , current_node ) ;
        push(current_node) ; //will push the current node on stack as a checkpoint
        return i+1 ; //direction goes from 1 to 8         
    }
}
//check_explored() ends here
